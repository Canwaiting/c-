#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
static int pipefd[2];

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL ); /*F_GETFL return a file access and status flags*/
    int new_option = old_option | O_NONBLOCK; /*old_option + O_NONBLOCK*/
    fcntl( fd, F_SETFL, new_option ); /*set the fd flags to new option*/
    return old_option; /*we still need the fd access,but just need it non blocking*/
}

void addfd( int epollfd, int fd )
{
    epoll_event event;  /*make a list for interesting event happen*/
    event.data.fd = fd;  /*find out which fd interesting*/
    event.events = EPOLLIN | EPOLLET;  /*can read | fd et notification*/
    /*todo not real know*/
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event ); /*let fd and event add to epollfd*/
    setnonblocking( fd );
}

void sig_handler( int sig )
{
    int save_errno = errno;
    int msg = sig;
    send( pipefd[1], ( char* )&msg, 1, 0 );
    errno = save_errno;
}

/*
 * todo will it initailize a sigaction everytime?
 */
void addsig( int sig )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) ); /*initial all the sa by \0*/
    sa.sa_handler = sig_handler; /*set handle function*/
    sa.sa_flags |= SA_RESTART;  /*restart the system that send this flag a|=b equal a=a|b*/
    sigfillset( &sa.sa_mask ); /*initialize and fill a signal set */
    assert( sigaction( sig, &sa, NULL ) != -1 ); /*check save the signal in sig successful or not*/
}

int main( int argc, char* argv[] )
{
    /*check normal input argument*/
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    /*initial info*/
    int ret = 0;  /*todo why we need that */
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    /*create socket*/
    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );

    //int nReuseAddr = 1;
    //setsockopt( listenfd, SOL_SOCKET, SO_REUSEADDR, &nReuseAddr, sizeof( nReuseAddr ) );

    /*bind*/
    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    if( ret == -1 )
    {
        printf( "errno is %d\n", errno );
        return 1;
    }
    //assert( ret != -1 );

    /*listen*/
    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    /*todo*/
    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 ); /*why we need the epoll*/
    assert( epollfd != -1 );
    addfd( epollfd, listenfd ); //todo addfd whay is it

    /*
     * create a pair of connected sockets that are pipe[0] and pipe[1]
     * todo but why we need that
     * todo and it will listen like the connect?
     */
    ret = socketpair( PF_UNIX, SOCK_STREAM, 0, pipefd );
    assert( ret != -1 );
    setnonblocking( pipefd[1] ); /*use for write*/
    addfd( epollfd, pipefd[0] ); /*use for read*/

    // add all the interesting signals here
    addsig( SIGHUP );
    addsig( SIGCHLD );
    addsig( SIGTERM );
    addsig( SIGINT );
    bool stop_server = false; /*todo dont know*/

    while( !stop_server )
    {
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }
    
        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;  /*just to see who interested*/
            /*if the interested is a new client want to connect to the server */
            if( sockfd == listenfd )
            {
                /*initialize client info*/
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                /*handle connect request*/
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                /*let client into the epoll*/
                addfd( epollfd, connfd );
            }
            /*if interested is a socket already in the server list the data can read*/
            else if( ( sockfd == pipefd[0] ) && ( events[i].events & EPOLLIN ) )
            {
                int sig;
                char signals[1024];
                /*return how many fd can read*/
                ret = recv( pipefd[0], signals, sizeof( signals ), 0 ); /*receive the signals*/
                if( ret == -1 )
                {
                    continue;
                }
                else if( ret == 0 )
                {
                    continue;
                }
                else
                {
                    for( int i = 0; i < ret; ++i )
                    {
                        //printf( "I caugh the signal %d\n", signals[i] );
                        /*deal with the signal*/
                        switch( signals[i] )
                        {
                            case SIGCHLD:
                            case SIGHUP:
                            {
                                continue;
                            }
                            case SIGTERM:
                            case SIGINT:
                            {
                                stop_server = true;
                            }
                        }
                    }
                }
            }
            else
            {
            }
        }
    }

    printf( "close fds\n" );
    close( listenfd );
    close( pipefd[1] );
    close( pipefd[0] );
    return 0;
}

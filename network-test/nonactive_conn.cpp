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
#include "lst_timer.h"

#define FD_LIMIT 65535
#define MAX_EVENT_NUMBER 1024
#define TIMESLOT 5

static int pipefd[2];
static sort_timer_lst timer_lst;
static int epollfd = 0;

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

void addfd( int epollfd, int fd )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}

void sig_handler( int sig )
{
    int save_errno = errno;
    int msg = sig;
    send( pipefd[1], ( char* )&msg, 1, 0 );
    errno = save_errno;
}

void addsig( int sig )
{
    /*initialize a sigaction*/
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset( &sa.sa_mask );

    /*catch the sig into the &sa to deal with null before*/
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

void timer_handler()
{
    timer_lst.tick();
    alarm( TIMESLOT );
}

/*TODO: use to close the fd?*/
void cb_func( client_data* user_data )
{
    epoll_ctl( epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0 );
    assert( user_data ); /*if there is null,return error*/
    close( user_data->sockfd );
    printf( "close fd %d\n", user_data->sockfd );
}

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );

    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    /*create the epoll*/
    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );
    addfd( epollfd, listenfd );

    /*just like create a pipe to connect*/
    ret = socketpair( PF_UNIX, SOCK_STREAM, 0, pipefd );
    assert( ret != -1 );
    setnonblocking( pipefd[1] ); /*use for write,so it is in the client side*/
    addfd( epollfd, pipefd[0] ); /*use for read,so it is in the server side*/


    /*todo set it everytime?*/
    addsig( SIGALRM );
    addsig( SIGTERM );
    bool stop_server = false; /*set up a start sign*/

    /*like epoll store the client info*/
    client_data* users = new client_data[FD_LIMIT]; 
    bool timeout = false;
    alarm( TIMESLOT ); /*todo set a clock*/

    while( !stop_server )
    {
        /*todo may be like epoll*/
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );

        /*epoll_wait not be used and system break*/
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }
    
        for ( int i = 0; i < number; i++ )
        {
            /*catch the fd now*/
            int sockfd = events[i].data.fd;

            /*have a client to connect*/
            if( sockfd == listenfd )
            {
                /*initial the client info*/
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );

                /*make a connect*/
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                /*add this to the epoll*/
                addfd( epollfd, connfd );
                /*update the users connfd*/
                users[connfd].address = client_address; /*address*/
                users[connfd].sockfd = connfd; /*fd*/

                /**/
                util_timer* timer = new util_timer; /*create a timer*/
                timer->user_data = &users[connfd]; /*bind the timer to this fd*/
                timer->cb_func = cb_func; /*todo what is cb_func */
                time_t cur = time( NULL ); /*initialize the current time*/
                timer->expire = cur + 3 * TIMESLOT; /*set up the expire time*/
                users[connfd].timer = timer; /*bind the timer to the user*/
                timer_lst.add_timer( timer ); /*add the timer to the clock chain*/
            }

            /*todo where have something can read*/
            else if( ( sockfd == pipefd[0] ) && ( events[i].events & EPOLLIN ) )
            {
                /*make a signal*/
                int sig;
                char signals[1024]; /*use for store the signal*/

                /*
                 * use for read the signal
                 * receive the signal to the signals buffer
                 */
                ret = recv( pipefd[0], signals, sizeof( signals ), 0 );

                /*todo notsure it means nonblocking*/
                if( ret == -1 )
                {
                    // handle the error
                    continue;
                }

                /*todo notsure shutdown or the client send 0 length data*/
                else if( ret == 0 )
                {
                    continue;
                }

                /*
                 * todo need to debug
                 * todo see the ret return
                 *
                 */
                else
                {
                    /*check the signals*/
                    for( int i = 0; i < ret; ++i )
                    {
                        switch( signals[i] )
                        {
                            /*ALARM CLOCK*/
                            case SIGALRM:
                            {
                                timeout = true;
                                break;
                            }

                            /*disconnect*/
                            case SIGTERM:
                            {
                                stop_server = true;
                            }
                        }
                    }
                }
            }

            /*todo where have write something*/
            else if(  events[i].events & EPOLLIN )
            {
                /*receive the data*/
                memset( users[sockfd].buf, '\0', BUFFER_SIZE );
                ret = recv( sockfd, users[sockfd].buf, BUFFER_SIZE-1, 0 );
                printf( "get %d bytes of client data %s from %d\n", ret, users[sockfd].buf, sockfd );

                /*get a timer */
                util_timer* timer = users[sockfd].timer;

                /*error*/
                if( ret < 0 )
                {
                    if( errno != EAGAIN )
                    {
                        cb_func( &users[sockfd] );
                        if( timer )
                        {
                            timer_lst.del_timer( timer );
                        }
                    }
                }

                /*nothing*/
                else if( ret == 0 )
                {
                    cb_func( &users[sockfd] );
                    if( timer )
                    {
                        timer_lst.del_timer( timer );
                    }
                }


                /*have something to receive and  */
                else
                {
                    //send( sockfd, users[sockfd].buf, BUFFER_SIZE-1, 0 );
                    if( timer )
                    {
                        time_t cur = time( NULL ); /*get current time*/
                        timer->expire = cur + 3 * TIMESLOT; /*set a alarm timer*/
                        printf( "adjust timer once\n" ); /*reset the timer*/
                        timer_lst.adjust_timer( timer ); /*if the timer timeout,let the timer move to the tail*/
                    }
                }
            }

            /*no do yet*/
            else
            {
                // others
            }
        }

        if( timeout )
        {
            timer_handler(); /*handle the clock*/
            timeout = false; /*reset the alarm*/
        }
    }

    /*close*/
    close( listenfd ); /*close the socket*/
    close( pipefd[1] ); /*close the server side*/
    close( pipefd[0] );/*close the client side*/
    delete [] users; /*free the memory*/
    return 0;
}

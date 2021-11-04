#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <poll.h>

#define USER_LIMIT 5  /*max num of users*/
#define BUFFER_SIZE 64  /*max num you can write*/
#define FD_LIMIT 65535  /*todo max num of fd*/

//todo
struct client_data
{
    sockaddr_in address;
    char* write_buf;
    char buf[ BUFFER_SIZE ];
};

//todo
int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );  //catch old way
    int new_option = old_option | O_NONBLOCK;   //add new way
    fcntl( fd, F_SETFL, new_option );
    return old_option;  //todo if return old,why we do that?
}


int main( int argc, char* argv[] )
{
    //check arg
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }

    //initial value
    const char* ip = argv[1];
    int port = atoi( argv[2] );
    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    //setup socket
    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );
    //bind
    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );
    //listen
    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    //create a limited userloop
    client_data* users = new client_data[FD_LIMIT];
    pollfd fds[USER_LIMIT+1];
    int user_counter = 0;
    for( int i = 1; i <= USER_LIMIT; ++i )  /*initial*/
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }

    //todo
    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;

    while( 1 )
    {
        //todo  user_counter+1 why need to +1
        ret = poll( fds, user_counter+1, -1 );
        if ( ret < 0 )
        { printf( "poll failure\n" );
            break;
        }

        /*poll all fd in server's side*/
        for( int i = 0; i < user_counter+1; ++i )
        {

            /* todo successfully connect and station
             * POLLIN
             * ( fds[i].revents & POLLIN ) return bollean
             * can read
             */
            if( ( fds[i].fd == listenfd ) && ( fds[i].revents & POLLIN ) )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                /*                 
                    todo try to make a connect with accept 
                    the connect is in client
                */
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );

                if ( connfd < 0 ) 
                {
                    printf( "errno is: %d\n", errno );
                    continue;
                }

                if( user_counter >= USER_LIMIT )
                {
                    const char* info = "too many users\n";
                    printf( "%s", info );
                    send( connfd, info, strlen( info ), 0 );    //send error info to client
                    close( connfd );    //close this connfd
                    continue;
                }

                //create a new user
                user_counter++; //why do that
                users[connfd].address = client_address;
                setnonblocking( connfd );   //todo maybe let connfd unblock
                fds[user_counter].fd = connfd;  //setup connect
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;    //listen what you can do
                fds[user_counter].revents = 0;  //nothing happen yet
                printf( "comes a new user, now have %d users\n", user_counter );
            }

            /* successfully connect and station
             * POLLERR
             * error
             */
            else if( fds[i].revents & POLLERR )
            {
                printf( "get an error from %d\n", fds[i].fd );  //info for specific socket

                char errors[ 100 ]; 
                memset( errors, '\0', 100 );
                socklen_t length = sizeof( errors );
                //why we need to get the opt
                if( getsockopt( fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length ) < 0 )
                {
                    printf( "get socket option failed\n" );
                }
                continue;
            }

            /* successfully connect and station
             * POLLRDHUP
             * hang up
             * such as write peer close then will return this to read peer
             */
            else if( fds[i].revents & POLLRDHUP )
            {
                users[fds[i].fd] = users[fds[user_counter].fd]; //todo why we need to do this 
                close( fds[i].fd ); //close the server socket
                fds[i] = fds[user_counter];
                i--;
                user_counter--; //close this socket
                printf( "a client left\n" );
            }

            /* successfully connect and station
             * POLLIN
             * can read
             */
            else if( fds[i].revents & POLLIN )
            {
                int connfd = fds[i].fd;
                memset( users[connfd].buf, '\0', BUFFER_SIZE );
                ret = recv( connfd, users[connfd].buf, BUFFER_SIZE-1, 0 );
                printf( "get %d bytes of client data %s from %d\n", ret, users[connfd].buf, connfd );
                if( ret < 0 )
                {
                    if( errno != EAGAIN )
                    {
                        close( connfd );
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                }
                else if( ret == 0 )
                {
                    printf( "code should not come to here\n" );
                }
                else
                {
                    for( int j = 1; j <= user_counter; ++j )
                    {
                        if( fds[j].fd == connfd )
                        {
                            continue;
                        }
                        
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[connfd].buf;
                    }
                }
            }

            /* successfully connect and station
             * POLLOUT
             * can write
             */
            else if( fds[i].revents & POLLOUT )
            {
                int connfd = fds[i].fd;
                if( ! users[connfd].write_buf )
                {
                    continue;
                }
                ret = send( connfd, users[connfd].write_buf, strlen( users[connfd].write_buf ), 0 );
                users[connfd].write_buf = NULL;
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }

    /*free and close*/
    delete [] users;
    close( listenfd );
    return 0;
}


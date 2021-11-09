#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

/* 0 is listen to itself
 * 1 is listen to other
 */

int main( int argc, char* argv[] ) //argc=count of arguments argv= arguments vector
{ 
    //print log
    if( argc <= 2 )
    {
        //where is in argb and argc
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );        
        return 1;
    }

    const char* ip = argv[1]; //what is in argv[0] 
    int port = atoi( argv[2] ); //atoi:let the string convert to the integer

    struct sockaddr_in server_address; //ipv4 socket address
    bzero( &server_address, sizeof( server_address ) ); //why use this 
    server_address.sin_family = AF_INET; //you just need it
    inet_pton( AF_INET, ip, &server_address.sin_addr ); //convert add to binary
    server_address.sin_port = htons( port ); //transfer the local port to the port in client need to use and bind it to the server
    int sockfd = socket( PF_INET, SOCK_STREAM, 0 ); //create a new socket 
    //todo sockfd>=0 what for
    assert( sockfd >= 0 ); //assert is a macro for find bug and limite the bug
    //if connect useful,real exsit
    if ( connect( sockfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) < 0 )
    {
        printf( "connection failed\n" );
        close( sockfd ); 
        return 1;
    }

    //todo dont know why set 0 , the 1 is normal
    pollfd fds[2];
    fds[0].fd = 0;  
    fds[0].events = POLLIN; 
    fds[0].revents = 0;
    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP; //have data to read||already shutdown
    fds[1].revents = 0;

    char read_buf[BUFFER_SIZE];
    int pipefd[2]; //[0] refers to read the end of the pipe [1] is write
    int ret = pipe( pipefd ); //what for
    assert( ret != -1 ); //for bugfree

    while( 1 )
    {

        ret = poll( fds, 2, -1 );
        //if didnot create the poll just return failure
        if( ret < 0 )
        {
            printf( "poll failure\n" );
            break;
        }


        //have event and already close
        if( fds[1].revents & POLLRDHUP )
        {
            printf( "server close the connection\n" );
            break;
        }

        //have date to read,print it 
        else if( fds[1].revents & POLLIN )
        {
            memset( read_buf, '\0', BUFFER_SIZE ); //dont know
            recv( fds[1].fd, read_buf, BUFFER_SIZE-1, 0 );
            printf( "%s\n", read_buf );
        }


        /*local event*/
        if( fds[0].revents & POLLIN )
        {
            /*
             *  write in the pipe
             */
            ret = splice( 0, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
            /*
             * read in the pipe
             */
            ret = splice( pipefd[0], NULL, sockfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE ); /*output from pipefd[0] to end*/
        }
    }
    
    close( sockfd );
    return 0;
}

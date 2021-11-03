#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main( int argc, char* argv[] )
{
    //check arguments right or not
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );//print filename
        return 1;
    }
    
    //setting ip port
    const char* ip = argv[1];    
    int port = atoi( argv[2] );

    //initial address
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );   //initial all to null or zero
    address.sin_family = AF_INET;  //ipv4
    inet_pton( AF_INET, ip, &address.sin_addr );    //convert from text to binary 
    address.sin_port = htons( port );   //convert from host byte order to network

    //setup socket
    int sock = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sock >= 0 );

    //bind
    int ret = bind( sock, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    //listen
    ret = listen( sock, 5 );
    assert( ret != -1 );

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof( client );

    //accpet
    int connfd = accept( sock, ( struct sockaddr* )&client, &client_addrlength ); 
    if ( connfd < 0 )
    {
        printf( "errno is: %d\n", errno );  //return error info
    }
    else    //successfully connect
    {
        //create a pip
        int pipefd[2];
        assert( ret != -1 );
        ret = pipe( pipefd );

        //write connfd->pip
        ret = splice( connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE ); 
        assert( ret != -1 );
        //read pip->connfd
        ret = splice( pipefd[0], NULL, connfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
        assert( ret != -1 );

        close( connfd );
    }

    close( sock );
    return 0;
}


/*
server:
    ./echo_server 127.0.0.1 12345 
client:
    telnet 127.0.0.1 12345
    Trying 127.0.0.1...
    Connected to 127.0.0.1.
    Escape character is '^]'.
    hello
    hello
    Connection closed by foreign host.
 */

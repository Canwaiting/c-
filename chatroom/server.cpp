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

#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535

int main() 
{
    //setup socket
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    //initial sockaddr_in
        //assignment
    //bind
    //listen
    //accept
    //function
    //close
}

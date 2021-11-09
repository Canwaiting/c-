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
#include <iostream>

using namespace std;


int main(int argc,char* argv[]){
    /*check arg*/
    if(argc<=2){
        cout<<basename(argv[0])<<endl;
        return 1;
    }

    /*setting ip and port*/
    int ret = 0;
    const char* ip=argv[1];
    int port = atoi(argv[2]); /*convert string to the int*/

    /*initialize server_address*/
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; /*family*/
    inet_pton(AF_INET,ip, &server_address.sin_addr);  /*address*/
    server_address.sin_port = htons(port);  /*port*/

    /*socket*/
    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd!=-1);

    /*connect*/
    ret = connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address)); 
    assert(ret!=-1);

    /*send message*/
    const char* message ="Hello!";
    send(sockfd,message,strlen(message),0); 

    /*close*/ 
    close(sockfd);



    
    return 0;
}



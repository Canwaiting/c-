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

#define BUF_SIZE 1024

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
    
    /*value the address*/
    struct sockaddr_in address; /*have family port address */
    bzero(&address,sizeof(address)); /*initialize data to zero*/
    address.sin_family = AF_INET; /*family-ip4*/
    inet_pton(AF_INET,ip,&address.sin_addr); /*convert text to binary and value */
    address.sin_port = htons(port); /*convert text to binary and value */ 

    /*create socket*/ 
    int listenfd = socket(PF_INET,SOCK_STREAM,0); /*ip4 todo*/ 
    assert(listenfd>=0);
    /*bind*/
    int ret_bind = bind(listenfd,(struct sockaddr*)&address,sizeof(address)); /*todo why*/
    assert(ret_bind!=-1);
    /*listen*/
    int ret_listen = listen(listenfd,5);
    assert(ret_listen!=-1);


    /*intialize client*/ 
    struct sockaddr_in client; 
    socklen_t client_addrlength = sizeof(client);
    /*connect*/
    int connfd = accept(listenfd,(struct sockaddr*)&client,&client_addrlength); 
    assert(connfd!=-1);
    /*receive*/
    char buffer[BUF_SIZE];
    memset(buffer,'\0',BUF_SIZE);
    ret = recv(connfd,buffer,BUF_SIZE-1,0);
    printf("socket:%d\n",listenfd);
    printf("bind:%d\n",ret_bind);
    printf("listen:%d\n",ret_listen);
    printf("connfd:%d\n",connfd);
    printf("ret:%d\n",ret);
    printf("we get %d byte char:%s\n",ret,buffer); 
    close(connfd);
    /*close*/ 
    close(listenfd); 
    return 0;
}


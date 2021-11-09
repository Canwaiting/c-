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
    ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address)); /*todo why*/
    assert(ret!=-1);
    /*listen*/
    ret = listen(listenfd,5);  
    assert(ret!=-1);


    while(1){
        /*intialize client*/ 
        struct sockaddr_in client; 
        socklen_t client_addrlength = sizeof(client);
        /*connect*/
        int connfd = accept(listenfd,(struct sockaddr*)&client,&client_addrlength); 
        if(connfd<=0){
            printf("errno is:%d\n",errno);
        }
        else{
        } 
    }

    /*close*/ 
    close(listenfd); 

    return 0;
}


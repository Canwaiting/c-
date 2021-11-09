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
    const char* ip=argv[1];
    int port = atoi(argv[2]); /*convert string to the int*/
    
    /*value the address*/
    struct sockaddr_in address; /*have family port address */
    brezo(&address,sizeof(address)); /*initialize data to zero*/
    address.sin_family = AF_INET; /*family-ip4*/
    inet_pton(AF_INET,ip,&address.sin_addr); /*convert text to binary and value */
    address.port = htons(port); /*convert text to binary and value */ 

    /*create socket*/
    int listenfd = socket(PF_INET,SOCK_STREAM,0); /*ip4 todo*/ 
    /*bind*/
    //todo why we need to ret
    ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address)); /*todo why*/
    /*listen*/
    ret = listen(listenfd,5);  //todo what will return










    return 1;
}


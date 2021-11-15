#include <sys.socket.h>
#include <stdio.h>
#include <assert.h>

#define LISTENQ 1024;

int main(int argc,char* argv[]){ 
    /*initialize var*/
    int ret = 0;
    int optval = 1; 
    struct sockaddr_in clientaddr; 
    //check the arg
    if(argc <= 2){
        printf("usage: %s port"basename(argv[0]));
        return 1;
    };
    
    /*initialize the port*/
    port = atoi(argv[1]); 

    //create a socket
    int listenfd = socket(AF_INET,SOCK_STREAM,0); 
    assert(listenfd!=-1); 

    /*eliminates 'in use' error from bind*/
    ret =  setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&optval,sizeofo(int));
    assert(ret!=-1);

    /*initialize the address */
    struct sockaddr_in address; 
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s.addr = htonl(INADDR_ANY); /*INADDR_ANY accpet any incoming*/
    address.sin_port = htons(port); 

    //bind
    ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
    assert(ret!=-1); 

    //listen
    ret = listen(listenfd,LISTENQ);
    assert(ret!=-1); 


    while(1){

        /*initialize client address length*/
        socklen_t clientaddr_len = sizeof()

        /*accpet*/
        int connfd = accpet(listenfd,(struct sockaddr*)&clientaddr,&clientaddr_len);
        assert(connfd!=-1);

        /*doit*/



        /*close*/
        close(connfd);
    }

    

















    
    return 0;
}

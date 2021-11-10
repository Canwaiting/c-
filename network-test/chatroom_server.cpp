#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h> #include <poll.h>
#include <iostream>

#define BUFFER_SIZE 64 
#define FD_LIMIT 65535
#define USER_LIMIT 5

using namespace std;

struct client_data{
    sockaddr_in address;
    char* write_buf;
    char buf[BUFFER_SIZE];
}

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

    /*set client array*/
    client_data* users = new client_data[FD_LIMIT];  /*todo assume have many event*/
    pollfd fds[USER_LIMIT+1]; //todo why we need one more
    int user_counter = 0;
    /*initialize the fds[1~end]*/
    for(int i = 1;i<=USER_LIMIT;++i){
        fds[i].fd = -1;
        fds[i].events = 0; 
    }
    
    /*fds[0]use to listen*/
    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;

    while(1){
        /*create a poll*/
        ret = poll(fds,user_counter+1,-1);
        assert(ret!=-1);
        /*start to poll*/
        for(int i = 0;i<user_counter+1;++i){
            /*
             * have a client
             * checkout if listen and someone want to connect
             */
            if((fds[i].fd==listenfd)&&(fds[i].revents & POLLIN)){
                /*make a connect*/
                struct sockaddr_in client_address;
                socklen_t client_addrelength = sizeof(client_address);
                int connfd = accept(listenfd,(struct sockaddr*)&client_address,&client_addrlength); /*returns a new file descriptor*/ 
                assert(connfd!=-1); 
                /*
                 * check if client enough
                 * actually the space is USER_LIMIT+1
                 * the fds[0] is use for listen to the new user 
                 */
                if(user_counter>=USER_LIMIT){
                    /*print error info*/
                    const* char info ="too many user\n"; 
                    printf("%s",info);
                    /*send disconnect to client */
                    send(connfd,info,strlen(info),0);
                    /*close the connect*/ 
                    close(connfd); 
                    continue;
                }
                /*user++*/
                user_counter++;
                /*record the user info and interest*/
                users[connfd].address = client_address;
                setnonblocking(connfd);
                /*record the new user to the fds */
                fds[user_counter].fd = connfd;
                /*have data to read | maybe hangup| error */
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                fds[user_counter].revents = 0;
                /*print the message*/
                printf("add a new user\n number_user:%d\n",user_counter);
            }
            /*error*/
            else if(fds[i].revents & POLLERR){
                /*print error message*/
                printf("get an error from %d\n",fds[i].fd);
                /*send error message to client*/
                /*clear socket error info and status*/ 
                //todo 
                char errors[100]; /*initialize*/ 
                memset(errors,'\0',100);
                socklen_t length = sizeof(errors);
                if(getsockopt(fds[i].fd,SOL_SOCKET,SO_ERROR,&errors,&length)<0){
                    printf("can not get the socket error option");
                }
            }
            /*hang up*/
            else if(fds[i].revents & POLLRDHUP){
                /*update the users*/
                users[fds[i].fd] = users[fds[user_counter].fd]; 
                /*close the connect*/
                close(fds[i].fd); 
                /*update the fds*/
                fds[i] = fds[user_counter];
                /*update the data*/
                i--;
                user_counter--;
                /*print message*/
                printf("a clinet left\n");
            }
            /*read something*/
            else if(fds[i].revents & POLLIN){
                /**/
                int connfd = fds[i].fd;
                memset(users[connfd].buf,'\0',BUFFER_SIZE); /*initialize buffer*/
                ret = recv(connfd,users[connfd].buf,BUFFER_SIZE-1,0); /*receive data*/
                /*error*/
                if(ret<0){
                    if(errno!=EAGAIN){
                        /*close connect*/
                        close(connfd);
                        /*update the users*/
                        users[fds[i].fd] = users[fds[user_counter].fd];  
                        /*update the fds*/
                        fds[i] = fds[user_counter];
                        /*update the data*/
                        i--;
                        user_counter--; 
                    }
                }
                else
                printf("bytes:%d\ncontext:%d\nclient:%d\n",ret,user[connfd].buf,connfd);
            }
            /*write something*/
            else if(fds[i].revents & POLLOUT){
                /**/
                int 
            }
        }


    }



    /*free the users*/
    if(users!=null){
        delete[] users; 
    }
    /*close*/ 
    close(listenfd); 
    return 0;
}


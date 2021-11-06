## mytalk

how poll work
    "users" is in the client side,but server need it to arrange the client
    client_data[]				-->users 
    sockaddr_in address;
	char* write_buf;
	char buf[ BUFFER_SIZE ];


--- 

    "fds" is in the server side use for listen all the fd had connecting
    a bunch of fd               -->fds[]
    fds[0].fd = listenfd           pollfd fds[USER_LIMIT+1] 
    "listenfd" is "socket"(bind listen)


---
    if( ( fds[i].fd == listenfd ) && ( fds[i].revents & POLLIN ) ) 

---

| client  | op_client     | server | op_server              |
|---------|---------------|--------|------------------------|
| socket  |               | socket |                        |
|         |               | listen |                        |
|         |               | bind   |                        |
| connect | users[user++] | accpet | users[user++] fds[i++] |
| connect | users[user++] | accpet | users[user++] fds[i++] |
| .       |               | .      |                        |
| .       |               | .      |                        |
| .       |               | .      |                        |
| connect | users[user++] | accpet | users[user++] fds[i++] |


---
client and server use whose socket in the datatransfer
| client        | op              | server        |
|---------------|-----------------|---------------|
| client_socket | <--something--> | server_socket |


---
how a socket station change in client and server
    the socket address never change,but the core have changed 
    bind listen function hvae return value and actually do work
        int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
        ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
        ret = listen( listenfd, 5 );

---
how data transfer

| client_socket                     | opt     | server_socket                 |
|-----------------------------------|---------|-------------------------------|
| setup socket                      |         | setup socket                  |
|                                   |         | bind                          |
|                                   |         | listen                        |
| connection                        |         | accept                        |
| data--send-->socket(connectioned) | somehow | data--recv-->socket(accepted) |
|                                   |         |                               |
|                                   |         |                               |
|                                   |         |                               |

## multi_port
    multi_port-->epoll theory
        epoll
            how it work
                how it listen to the event
                    select and poll learn not enough



        



    what is that mean
        if 
        for
        else

        fds[0]use for check new user
        fds[1-5]use for real user



















## todo 
---
todo the number listen bind return maybe meaning something


--- 
+ todo what is something in here
    client_socket   <--something-->   server socket  

+ todo how socket file content change during setup to close

---
+ todo we actually dont know chatroom datastructure inside 
    you can watch unp


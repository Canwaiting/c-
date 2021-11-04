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
| connect       | users[user++] | accpet        | users[user++] fds[i++] |
|---------------|---------------|---------------|------------------------|
| client_socket |               | server_socket |                        |


---
how a socket station change in client and server
    the socket address never change,but the core have changed 
        int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
        ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
        ret = listen( listenfd, 5 );



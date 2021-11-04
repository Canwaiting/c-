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
        client      server socket socket                               
                     bind
            listen
connect-->user++     accept-->fd++ user++

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


client and server use whose socket in the datatransfer
| connect | users[user++] | accpet | users[user++] fds[i++] |

#define TIMEOUT 5000

/*initial the time*/
int timeout = TIMEOUT;
time_t start = time( NULL );
time_t end = time( NULL );

while( 1 )
{
    printf( "the timeout is now %d mill-seconds\n", timeout );
    /**/
    start = time( NULL );

    /*return the time clock or event*/
    int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, timeout );

    /*error handle*/
    if( ( number < 0 ) && ( errno != EINTR ) )
    {
        printf( "epoll failure\n" );
        break;
    }

    /*the maxevents  argument  must  be greater than zero.*/
    if( number == 0 )
    {
        // timeout
        timeout = TIMEOUT;
        continue;
    }

    /*record the end time*/
    end = time( NULL );

    /*minus the epoll_wait run time*/
    timeout -= ( end - start ) * 1000;

    /*recheck the timeout */
    if( timeout <= 0 )
    {
        // timeout
        timeout = TIMEOUT;
    }

    // handle connections
}

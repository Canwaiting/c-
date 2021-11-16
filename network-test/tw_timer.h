#ifndef TIME_WHEEL_TIMER
#define TIME_WHEEL_TIMER

#include <time.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 64
class tw_timer;

/*client data*/
struct client_data
{
    sockaddr_in address; /*address*/
    int sockfd; /*the file desriptor*/
    char buf[ BUFFER_SIZE ]; /*TODO*/
    tw_timer* timer; /*TODO*/
};

class tw_timer
{
/*TODO:know the meaning,dont know the gammer*/
public:
    tw_timer( int rot, int ts )
    : next( NULL ), prev( NULL ), rotation( rot ), time_slot( ts ){}

public:
    int rotation; /*TODO*/
    int time_slot; /*which slot*/
    void (*cb_func)( client_data* ); /*TODO:gammer*/
    client_data* user_data; /*TODO*/
    tw_timer* next; /*TODO*/
    tw_timer* prev; /*TODO*/
};

class time_wheel
{
public:
    /*initialize the whole time_wheel*/
    time_wheel() : cur_slot( 0 )
    {
        /*initialize the every single slot*/
        for( int i = 0; i < N; ++i )
        {
            slots[i] = NULL; /*let it be the null list*/
        }
    }

    /*clear all the timer in the slot*/
    ~time_wheel()
    {
        for( int i = 0; i < N; ++i )
        {
            tw_timer* tmp = slots[i];
            /*delete from begin to the end*/
            while( tmp )
            {
                slots[i] = tmp->next; /*move the slot[i]*/
                delete tmp; /*delete the temp*/
                tmp = slots[i]; /*move the temp*/
            }
        }
    }

    tw_timer* add_timer( int timeout )
    {
        /*error*/
        if( timeout < 0 )
        {
            return NULL;
        }

        /*TODO*/
        int ticks = 0;

        if( timeout < TI )
        {
            ticks = 1;
        }
        else
        {
            ticks = timeout / TI;
        }
        int rotation = ticks / N;
        int ts = ( cur_slot + ( ticks % N ) ) % N;
        tw_timer* timer = new tw_timer( rotation, ts );
        if( !slots[ts] )
        {
            printf( "add timer, rotation is %d, ts is %d, cur_slot is %d\n", rotation, ts, cur_slot );
            slots[ts] = timer;
        }
        else
        {
            timer->next = slots[ts];
            slots[ts]->prev = timer;
            slots[ts] = timer;
        }
        return timer;
    }
    void del_timer( tw_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        int ts = timer->time_slot;
        if( timer == slots[ts] )
        {
            slots[ts] = slots[ts]->next;
            if( slots[ts] )
            {
                slots[ts]->prev = NULL;
            }
            delete timer;
        }
        else
        {
            timer->prev->next = timer->next;
            if( timer->next )
            {
                timer->next->prev = timer->prev;
            }
            delete timer;
        }
    }
    void tick()
    {
        tw_timer* tmp = slots[cur_slot];
        printf( "current slot is %d\n", cur_slot );
        while( tmp )
        {
            printf( "tick the timer once\n" );
            if( tmp->rotation > 0 )
            {
                tmp->rotation--;
                tmp = tmp->next;
            }
            else
            {
                tmp->cb_func( tmp->user_data );
                if( tmp == slots[cur_slot] )
                {
                    printf( "delete header in cur_slot\n" );
                    slots[cur_slot] = tmp->next;
                    delete tmp;
                    if( slots[cur_slot] )
                    {
                        slots[cur_slot]->prev = NULL;
                    }
                    tmp = slots[cur_slot];
                }
                else
                {
                    tmp->prev->next = tmp->next;
                    if( tmp->next )
                    {
                        tmp->next->prev = tmp->prev;
                    }
                    tw_timer* tmp2 = tmp->next;
                    delete tmp;
                    tmp = tmp2;
                }
            }
        }
        cur_slot = ++cur_slot % N;
    }

private:
    static const int N = 60; /*the slot number*/
    static const int TI = 1; /*tick time is 1s*/
    tw_timer* slots[N]; /*every slot in the wheel*/
    int cur_slot; /*current slot*/
};

#endif

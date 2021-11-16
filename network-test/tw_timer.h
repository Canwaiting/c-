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
    int rotation; /*how many round*/
    int time_slot; /*which slot*/
    void (*cb_func)( client_data* ); /*TODO:call back*/
    client_data* user_data; /*TODO*/

    /* timer<--(prev)timer(next)-->timer */
    tw_timer* next;
    tw_timer* prev;
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

    /*add the timer*/
    tw_timer* add_timer( int timeout )
    {
        /*error*/
        if( timeout < 0 )
        {
            return NULL;
        }

        /*how many tick the timer need before alarm*/
        int ticks = 0; /*initialize*/
        /*if timeout less than TI,equal 1 tick*/
        if( timeout < TI )
        {
            ticks = 1;
        }

        /*else just get the integer*/
        else
        {
            ticks = timeout / TI;
        }

        /*calculate how many round the timer need before alarm*/
        int rotation = ticks / N;

        /*which slot should timer in*/
        int ts = ( cur_slot + ( ticks % N ) ) % N;

        /*make a new timer in ts slot,which will alarm when spin roation*/
        tw_timer* timer = new tw_timer( rotation, ts );

        /*if the slots is null,add it and put it to the head pointer*/
        if( !slots[ts] )
        {
            printf( "add timer, rotation is %d, ts is %d, cur_slot is %d\n", rotation, ts, cur_slot );
            slots[ts] = timer;
        }

        /*add it to the before*/
        else
        {
            timer->next = slots[ts];
            slots[ts]->prev = timer;
            slots[ts] = timer; /*timer become the head */
        }

        /*return a timer which already have position*/
        return timer;
    }

    /*delete the timer*/
    void del_timer( tw_timer* timer )
    {
        /*check null or not*/
        if( !timer )
        {
            return;
        }

        /*get the slot position*/
        int ts = timer->time_slot;

        /*if timer is the head*/
        if( timer == slots[ts] )
        {
            /*move the head to the next*/
            slots[ts] = slots[ts]->next;

            /*if have next*/
            if( slots[ts] )
            {
                /*separate the timer*/
                slots[ts]->prev = NULL;
            }

            delete timer;
        }

        /*not in the head*/
        else
        {
            /*get rid of the prev*/
            /*1(next)-->timer-->2*/
            timer->prev->next = timer->next;
            /*1(next)-->2*/

            /*get rid of the next,if have next*/
            if( timer->next )
            {
                /*1-->timer<--(prev)2*/
                timer->next->prev = timer->prev;
                /*1<--(prev)2*/
            }
            delete timer;
        }
    }

    /*when tick time done,call tick(),which use to move a slot forward*/
    void tick()
    {
        /*get the current slot's head*/
        tw_timer* tmp = slots[cur_slot];
        printf( "current slot is %d\n", cur_slot );

        /*check all current slot timer list*/
        while( tmp )
        {
            printf( "tick the timer once\n" );

            /*if not this round,update rotation and move temp to next*/
            if( tmp->rotation > 0 )
            {
                tmp->rotation--;
                tmp = tmp->next;
            }

            /*do the job and delete this timer*/
            else
            {
                tmp->cb_func( tmp->user_data ); /*TODO:maybe doit*/

                /*delete the timer,head*/
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

                /*delete the timer,not head*/
                else
                {
                    tmp->prev->next = tmp->next;
                    if( tmp->next )
                    {
                        tmp->next->prev = tmp->prev;
                    }
                    tw_timer* tmp2 = tmp->next; /*for keep going*/
                    delete tmp;
                    tmp = tmp2; /*move the next*/
                }
            }
        }

        /*update the current slot*/
        cur_slot = ++cur_slot % N; /*%N for cur_slot>N*/
    }

private:
    static const int N = 60; /*the slot number*/
    static const int TI = 1; /*tick time is 1s*/
    tw_timer* slots[N]; /*every slot in the wheel*/
    int cur_slot; /*current slot*/
};

#endif

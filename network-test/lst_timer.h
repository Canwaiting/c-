#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>

#define BUFFER_SIZE 64
class util_timer;

struct client_data
{
    sockaddr_in address; /*address*/
    int sockfd; /*socket fd*/
    char buf[ BUFFER_SIZE ]; /*buffer for write*/
    util_timer* timer; /*clock*/
};

class util_timer
{
public:
    util_timer() : prev( NULL ), next( NULL ){} /*double hand chain*/

public:
   time_t expire; /*time_t from 1970 to now,relative time*/
   void (*cb_func)( client_data* ); /*todo callback*/
   client_data* user_data;
   util_timer* prev; /*todo callback*/
   util_timer* next; /*todo callback*/
};

class sort_timer_lst
{
public:
    /*initialize*/
    sort_timer_lst() : head( NULL ), tail( NULL ) {}

    /*when destory,delete all the chain*/
    ~sort_timer_lst()
    {
        util_timer* tmp = head; /*temple space to delete*/
        /*keep delete the former until the head have nothing*/
        while( tmp )
        {
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }

    void add_timer( util_timer* timer )
    {
        /*timer is null,return*/
        if( !timer )
        {
            return;
        }

        /*head is null,the chain is a cycle point itself and return*/
        if( !head )
        {
            head = tail = timer;
            return; 
        }

        /*changer the position*/
        if( timer->expire < head->expire )
        {
            timer->next = head;
            head->prev = timer;
            head = timer; /*turn to original head to do that*/
            return;
        }
        add_timer( timer, head ); /*use another function*/
    }
    void adjust_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        util_timer* tmp = timer->next; /*timer-->tmp*/

        /*
         * no need to adjust if
         * timer-->temp(null)
         * expire<expire
         */
        if( !tmp || ( timer->expire < tmp->expire ) )
        {
            return;
        }

        /**/
        if( timer == head )
        {
            head = head->next;
            head->prev = NULL;
            timer->next = NULL;
            add_timer( timer, head );
        }
        else
        {
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            add_timer( timer, timer->next );
        }
    }
    void del_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        if( ( timer == head ) && ( timer == tail ) )
        {
            delete timer;
            head = NULL;
            tail = NULL;
            return;
        }
        if( timer == head )
        {
            head = head->next;
            head->prev = NULL;
            delete timer;
            return;
        }
        if( timer == tail )
        {
            tail = tail->prev;
            tail->next = NULL;
            delete timer;
            return;
        }
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        delete timer;
    }
    void tick()
    {
        if( !head )
        {
            return;
        }
        printf( "timer tick\n" );
        time_t cur = time( NULL );
        util_timer* tmp = head;
        while( tmp )
        {
            if( cur < tmp->expire )
            {
                break;
            }
            tmp->cb_func( tmp->user_data );
            head = tmp->next;
            if( head )
            {
                head->prev = NULL;
            }
            delete tmp;
            tmp = head;
        }
    }

private:
    void add_timer( util_timer* timer, util_timer* lst_head )
    {
        util_timer* prev = lst_head;
        util_timer* tmp = prev->next;
        while( tmp )
        {
            if( timer->expire < tmp->expire )
            {
                prev->next = timer;
                timer->next = tmp;
                tmp->prev = timer;
                timer->prev = prev;
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if( !tmp )
        {
            prev->next = timer;
            timer->prev = prev;
            timer->next = NULL;
            tail = timer;
        }
        
    }

private:
    util_timer* head;
    util_timer* tail;
};

#endif

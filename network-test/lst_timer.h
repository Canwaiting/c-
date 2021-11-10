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

    /*if the timer timeout,let the timer move to the tail*/
    void adjust_timer( util_timer* timer )
    {
        /*no timer,break the function*/
        if( !timer )
        {
            return;
        }
        util_timer* tmp = timer->next; /*timer-->tmp*/

        /*
         * no need to adjust if
         * the timer is the last one
         *     timer-->temp
         * or expire<expire state ascending
         */
        if( !tmp || ( timer->expire < tmp->expire ) )
        {
            return;
        }

        /*get it from the chain and re_put to the chain*/
        if( timer == head )
        {
            head = head->next; /*change the position*/
            head->prev = NULL; /*delete original prev*/
            timer->next = NULL; /*delete original next*/
            add_timer( timer, head ); /*add it to the chain again*/
        }
        else
        {
            /*
             * let the timer alone
             * before:1-->timer-->3
             * after: 1-->3    timer
             */
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            add_timer( timer, timer->next ); //todo
        }
    }

    /*delete the timer*/
    void del_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }

        /*only one timer*/
        if( ( timer == head ) && ( timer == tail ) )
        {
            /*free all the timer and pointer*/
            delete timer;
            head = NULL;
            tail = NULL;
            return;
        }

        /*
         * timer is the head
         * timer(head)-->2
         * 2(head)-->3
         */
        if( timer == head )
        {
            head = head->next;
            head->prev = NULL;
            delete timer;
            return;
        }

        /*
         * timer is the tail
         * 1-->2-->timer(tail)
         * 1-->2(tail)
         */
        if( timer == tail )
        {
            tail = tail->prev; /*change the position*/
            tail->next = NULL; /*separate the timer*/
            delete timer;
            return;
        }

        /*
         * 1-->timer-->2
         * 1-->2
         */
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
        time_t cur = time( NULL ); /*get the time by now*/

        /*todo from first timer to the end until find out the timeout one */
        util_timer* tmp = head; /*from the head*/
        while( tmp )
        {
            /*not timeout yet*/
            if( cur < tmp->expire )
            {
                break;
            }

            /*todo the callback*/
            tmp->cb_func( tmp->user_data );

            /*
             * 1-->2-->tmp-->4-->5
             * 1-->2-->tmp-->4(head)-->5
             */
            head = tmp->next;

            /*mean tmp not the last one*/
            if( head )
            {
                head->prev = NULL; /* 1-->2-->tmp||4(head)-->5*/
            }

            delete tmp; /* 1-->2-->null||4(head)-->5*/
            /*start from the 4*/
            tmp = head; /*4(head)(tmp)*/
        }
    }

private:
    /*
     * full list
     * 1-->2-->3-->4-->5-->lst_head-->...
     */
    void add_timer( util_timer* timer, util_timer* lst_head )
    {
        /* 1-->2-->3-->4-->5-->lst_head(prev)-->tmp...*/
        util_timer* prev = lst_head;
        util_timer* tmp = prev->next;

        /*from first to lase*/
        while( tmp )
        {
            /*keep ascending*/
            if( timer->expire < tmp->expire )
            {
                prev->next = timer; /* 1-->2-->3-->4-->5-->lst_head(prev)-->timer||tmp-->...*/
                /* 1-->2-->3-->4-->5-->lst_head(prev)-->timer-->tmp-->...*/
                timer->next = tmp;
                tmp->prev = timer;

                /* 1-->2-->3-->4-->5-->lst_head-->timer(prev)-->tmp-->...*/
                timer->prev = prev;
                break;
            }

            /*else go to next one*/
            prev = tmp; /* 1-->2-->3-->4-->5-->lst_head-->tmp(prev)...*/
            tmp = tmp->next; /* 1-->2-->3-->4-->5-->lst_head-->tmp(prev)-->tmp...*/
        }

        /*
         * still not find out who bigger than the timer
         * add it to the end
         */
        if( !tmp )
        {
            /* 1-->2-->3-->4-->5-->lst_head-->.....(prev)-->timer-->null...*/
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

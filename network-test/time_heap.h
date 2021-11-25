#ifndef intIME_HEAP
#define intIME_HEAP

#include <iostream>
#include <netinet/in.h>
#include <time.h>
using std::exception;

#define BUFFER_SIZE 64

class heap_timer;
struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[ BUFFER_SIZE ];
    heap_timer* timer;
};

class heap_timer
{
public:
    heap_timer( int delay )
    {
        expire = time( NULL ) + delay;
    }

public:
   time_t expire;
   void (*cb_func)( client_data* );
   client_data* user_data;
};

/*main function*/
class time_heap
{
public:
    /*initialize a heap by a null array*/
    time_heap( int cap ) throw ( std::exception ) /*TODO: throw exception*/
        : capacity( cap ), cur_size( 0 )
    {
	array = new heap_timer* [capacity];

    /*handle the error*/
	if ( ! array )
	{
            throw std::exception();
	}
        /*initialize the array*/
        for( int i = 0; i < capacity; ++i )
        {
            array[i] = NULL;
        }
    }

    /*initialize a heap by use an array already have*/
    /*TODO: whats difference between capacity and size*/
    time_heap( heap_timer** init_array, int size, int capacity ) throw ( std::exception )
        : cur_size( size ), capacity( capacity )
    {
        /*handle error(size error)*/
        if ( capacity < size )
        {
            throw std::exception();
        }

        array = new heap_timer* [capacity];

        /*handle error(initialize error)*/
        if ( ! array )
        {
            throw std::exception();
        }

        for( int i = 0; i < capacity; ++i )
        {
            array[i] = NULL;
        }

        /*if the init_array have element*/
        if ( size != 0 )
        {
            /*value the array*/
            for ( int i =  0; i < size; ++i )
            {
                array[ i ] = init_array[ i ];
            }

            /*order from bottom to the top,from left to right*/
            for ( int i = (cur_size-1)/2; i >=0; --i )
            {
                percolate_down( i );
            }
        }
    }

    /*destory the heap*/
    ~time_heap()
    {
        for ( int i =  0; i < cur_size; ++i )
        {
            delete array[i];
        }
        delete [] array; 
    }

public:
    void add_timer( heap_timer* timer ) throw ( std::exception )
    {
        /*check null error*/
        if( !timer )
        {
            return;
        }

        /*double the array if dont have enough space*/
        if( cur_size >= capacity )
        {
            resize();
        }

        /*make an empty hole*/
        int hole = cur_size++;

        /*initialize*/
        int parent = 0;

        /*percolate_up*/
        for( ; hole > 0; hole=parent )
        {
            /*get the parent*/
            parent = (hole-1)/2;

            /*the parent_timer<=add_timer*/
            if ( array[parent]->expire <= timer->expire )
            {
                break;
            }

            /*change the position*/
            array[hole] = array[parent];
        }

        /*add the timer to the hole*/
        array[hole] = timer;
    }

    /*TODO*/
    void del_timer( heap_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        // lazy delelte
        timer->cb_func = NULL;
    }

    /*get the top timer*/
    heap_timer* top() const
    {
        /*check empty or not*/
        if ( empty() )
        {
            return NULL;
        }

        return array[0];
    }

    /*pop out the top timer*/
    void pop_timer()
    {
        if( empty() )
        {
            return;
        }

        if( array[0] )
        {
            delete array[0];

            /*let the last to the first*/
            array[0] = array[--cur_size];
            /*re_percolate_down the top element*/
            percolate_down( 0 );
        }
    }

    /*tick function*/
    void tick()
    {
        /*TODO*/
        heap_timer* tmp = array[0];

        /*TODO:handle the timeout alarm*/
        time_t cur = time( NULL );

        /*TODO*/
        /*for git*/
        while( !empty() )
        {
            if( !tmp )
            {
                break;
            }
            if( tmp->expire > cur )
            {
                break;
            }
            if( array[0]->cb_func )
            {
                array[0]->cb_func( array[0]->user_data );
            }
            pop_timer();
            tmp = array[0];
        }
    }

    /*TODO:how it achieve the func*/
    bool empty() const { return cur_size == 0; }

private:
    /*let the smaller node to the root*/
    void percolate_down( int hole )
    {
        /*temp store*/
        heap_timer* temp = array[hole];

        /*initialize(dont have meaning)*/
        int child = 0;

        /*
         * TODO:just decide the node
         */
        for ( ; ((hole*2+1) <= (cur_size-1)); hole=child )
        {
            /*get the left child index*/
            child = hole*2+1;

            /*
             * not the last element
             * left_child_timeout < right_child_timeout
             * move the child
             */
            if ( (child < (cur_size-1)) && (array[child+1]->expire < array[child]->expire ) )
            {
                ++child; /*left child to the right child*/
            }

            /*change the position if hole_timer less than child_timer*/
            if ( array[child]->expire < temp->expire )
            {
                array[hole] = array[child];
            }

            /*the hole is the minimum*/
            else
            {
                break;
            }
        }

        /*change the node*/
        array[hole] = temp;
    }

    /*convert the original array to the double size*/
    void resize() throw ( std::exception )
    {
        /*make a double size array*/
        heap_timer** temp = new heap_timer* [2*capacity];

        /*initialize the new array*/
        for( int i = 0; i < 2*capacity; ++i )
        {
            temp[i] = NULL;
        }

        /*check null error*/
        if ( ! temp )
        {
            throw std::exception();
        }

        /*value the new capacity*/
        capacity = 2*capacity;

        /*transfer the value*/
        for ( int i = 0; i < cur_size; ++i )
        {
            temp[i] = array[i];
        }

        /*delete the old array*/
        delete [] array;

        /*change the array*/
        array = temp;
    }

private:
    heap_timer** array;
    int capacity;
    int cur_size;
};

#endif

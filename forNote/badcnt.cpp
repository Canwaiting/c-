#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; //创建锁
void *add_function( void *ptr ); //调用函数
volatile int cnt = 0; //全局变量
main()
{
    //创建线程
    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,add_function,NULL);
    pthread_create(&thread2,NULL,add_function,NULL); 

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL); 
    cout<<"Result: "<<cnt<<endl;

    exit(0);
}

void *add_function( void *ptr )
{
    pthread_mutex_lock(&mutex1);
    for(int i = 0;i<10000;i++)
        cnt++;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

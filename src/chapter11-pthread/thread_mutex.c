/*
 * =====================================================================================
 *
 *       Filename:  thread_mutex.c
 *
 *    Description:  演示多线程互斥锁控制
 *
 *        Version:  1.0
 *        Created:  2013年06月07日 23时02分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <pthread.h>

pthread_t tid_one;
pthread_t tid_two;
pthread_mutex_t  pmutex;
int total = 0;;

void* print_ids(const char*s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid(); // get tgid
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
            (unsigned int)tid, (unsigned int)tid);
}

void* thread_one(void *arg) {
   print_ids("thread one: ");

   int i = 0;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&pmutex);
        total --;
        printf("[thread #1] getlock, dec total = %d \n", total);
        pthread_mutex_unlock(&pmutex);

        usleep(1000 * 100);
    }

    printf("[thread #1] exit\n");
    pthread_exit(NULL);
}

void thread_two(void *arg) {
    print_ids("thread one: ");
    
    int i = 0;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&pmutex);
        total ++;
        printf("[thread #2] getlock, inc total = %d\n", total);
        pthread_mutex_unlock(&pmutex);

        usleep(1000 * 200);
    }
    printf("[thread #2] exit\n");
    pthread_exit(NULL);
}

int main() {

    // 初始化mutex
    pthread_mutex_init(&pmutex, NULL);

    // 创建两个线程
    int err;
    err = pthread_create(&tid_one, NULL, thread_one, NULL);
    if (err != 0) {
        err_quit("cannot create thread one");
    }

    err = pthread_create(&tid_two, NULL, thread_two, NULL);
    if (err != 0) {
        err_quit("cannot create thread two");
    }

    // 等待线程完成(阻塞)
    pthread_join(tid_one, NULL);
    printf("[main] thread 1 exit\n");
    
    pthread_join(tid_two, NULL);
    printf("[main] thread 2 exit\n");
}




/*
 * =====================================================================================
 *
 *       Filename:  pthread_sig.c
 *
 *    Description:  演示使用线程同步处理信号
 *
 *        Version:  1.0
 *        Created:  2013年06月10日 11时00分09秒
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

int quit_flag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait = PTHREAD_COND_INITIALIZER;

void thread_f(void* arg) {
    int err, signo;

    for (;;) {
        err = sigwait(&mask, &signo);
        if (err != 0) {
            err_exit(err, "sigwait failed");
        }

        switch (signo) {
            case SIGINT:
                printf("\n[thread]interrupt\n");
                break;
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quit_flag = 1;
                pthread_mutex_unlock(&lock);
                pthread_cond_signal(&wait);
                return 0;
            default:
                printf("\n[thread]unexprected signal\n");
        }
    }
}

int main(void) {
    int err;
    sigset_t oldmask;
    pthread_t tid;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    pthread_sigmask(SIG_BLOCK, &mask, &oldmask);
    pthread_create(&tid, NULL, thread_f, 0);

    // 加锁访问条件变量
    pthread_mutex_lock(&lock);
    while(quit_flag == 0) {
        pthread_cond_wait(&wait, &lock);
    }
    pthread_mutex_unlock(&lock);

    quit_flag = 0;
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
}






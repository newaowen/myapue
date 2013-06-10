/*
 * =====================================================================================
 *
 *       Filename:  print_thread.c
 *
 *    Description:  打印线程数据
 *
 *        Version:  1.0
 *        Created:  2013年06月05日 23时11分04秒
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

pthread_t ntid;

void print_ids(const char*s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
            (unsigned int)tid, (unsigned int)tid);
}

void thr_fn(void *arg) {
    print_ids("new thread: ");
    return ((void*)0);
}

int main(void) {
    int err;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0) {
        err_quit("cannot create thread");
    }
    print_ids("main thread: ");
    // 防止主线程退出进程，导致新线程没有时间执行
    sleep(2);
    printf("main thread exit\n");
}

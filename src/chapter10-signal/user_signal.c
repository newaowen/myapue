/*
 * =====================================================================================
 *
 *       Filename:  user_signal.c
 *
 *    Description:  演示SIGUSR使用, signal系统调用设置的信号处理只能生效一次，然后又变回默认的信号处理函数了．
 *                  默认的就是退出进程!
 *              
 *
 *        Version:  1.0
 *        Created:  2013年06月05日 12时33分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"

static void sig_usr(int);

int main(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        err_sys("catch SIGUSR1 err");
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        err_sys("catch SIGUSR2 err");
    }

    for(;;) {
        pause();
    }
}

static void sig_usr(int signo) {
    if (signo == SIGUSR1) {
        printf("sigusr1 received\n");
    } else if (signo == SIGUSR2) {
        printf("sigusr2 received\n");
    } 
}

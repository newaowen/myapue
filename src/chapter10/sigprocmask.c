/*
 * =====================================================================================
 *
 *       Filename:  sigprocmask.c
 *
 *    Description:  信号集设置demo
 *                  执行：./sigprocmask
 *                      输入 ^\ (ctrl+\)
 *
 *        Version:  1.0
 *        Created:  2013年06月05日 20时42分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"

static void sig_quit(int);

int main(void) {
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        err_sys("catch sigquit error");
    }

    sigemptyset(&newmask);

    // 添加sigquit block
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        err_sys("sig block error");
    }
    printf("go to sleep...\n");
    sleep(3);
    printf("sleep over...\n");

    if (sigpending(&pendmask) < 0) {
        err_sys("sigpending error");
    }

    if (sigismember(&pendmask, SIGQUIT)) {
        printf("\nsigquit pending\n");
    }

    // 在重置信号集后（解除信号阻塞），如果有信号处于pending状态
    // 则解除后先执行信号处理程序，然后再走main下面的流程
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        err_sys("sig_setmask error");
    }

    printf("sigquit ublocked\n");
    
    sleep(5);
}

static void sig_quit(int signo) {
    printf("catch sigquit\n");
    // 重置sigquit信号
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        err_sys("cannot reset sigquit");
    }
}

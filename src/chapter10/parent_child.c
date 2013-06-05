/*
 * =====================================================================================
 *
 *       Filename:  parent_child.c
 *
 *    Description:  ���ӽ��������ź���ͬ��demo
 *
 *        Version:  1.0
 *        Created:  2013��06��05�� 22ʱ12��05��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) {
    sigflag = 1;
}

void TELL_WAIT(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        err_sys("signal sigusr1 error");
    }

    signal(SIGUSR2, sig_usr);

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    // block usr1
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
}

void TELL_PARENT(pid_t pid) {
    kill(pid, SIGUSR2);
}

void WAIT_PARENT(void) {
    while (sigflag == 0) {
        sigsuspend(&zeromask);
    }

    sigflag = 0;

    // reset mask
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

void TELL_CHILD(pid_t pid) {
    kill(pid, SIGUSR1);
}

void WAIT_CHILD(void) {
    while (sigflag == 0) {
        sigsuspend(&zeromask);
    }

    sigflag = 0;
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    }
}

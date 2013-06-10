/*
 * =====================================================================================
 *
 *       Filename:  sigprocmask.c
 *
 *    Description:  �źż�����demo
 *                  ִ�У�./sigprocmask
 *                      ���� ^\ (ctrl+\)
 *
 *        Version:  1.0
 *        Created:  2013��06��05�� 20ʱ42��34��
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

    // ���sigquit block
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

    // �������źż��󣨽���ź���������������źŴ���pending״̬
    // ��������ִ���źŴ������Ȼ������main���������
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        err_sys("sig_setmask error");
    }

    printf("sigquit ublocked\n");
    
    sleep(5);
}

static void sig_quit(int signo) {
    printf("catch sigquit\n");
    // ����sigquit�ź�
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        err_sys("cannot reset sigquit");
    }
}

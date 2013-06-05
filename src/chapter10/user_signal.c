/*
 * =====================================================================================
 *
 *       Filename:  user_signal.c
 *
 *    Description:  ��ʾSIGUSRʹ��, signalϵͳ�������õ��źŴ���ֻ����Чһ�Σ�Ȼ���ֱ��Ĭ�ϵ��źŴ������ˣ�
 *                  Ĭ�ϵľ����˳�����!
 *              
 *
 *        Version:  1.0
 *        Created:  2013��06��05�� 12ʱ33��19��
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

/*
 * =====================================================================================
 *
 *       Filename:  sleep2.c
 *
 *    Description:  ������������sleep2ʵ�֣��������������źŴ�����������)
 *
 *        Version:  1.0
 *        Created:  2013��06��05�� 13ʱ15��16��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
 #include <setjmp.h>


unsigned int sleep2(unsigned int);
static void sig_int(int);

static jmp_buf env_alrm;

static void sig_alrm(int signo) {
    longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int nsec) {
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        return nsec;
    }

    if (setjmp(env_alrm) == 0) {
        alarm(nsec);
        pause();
    }

    return alarm(0);
}
int main() {
    unsigned int unslept;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        err_sys("signal error");
    }

    unslept = sleep2(2);
    printf("sleep2 returned:%u \n", unslept);
}

// int�źŴ��������ʱ��ϳ����ܿ��ܱ�sleep��ǰ��ֹ(longjmp��ת)
static void sig_int(int signo) {
    int i, j;
    volatile int k;

    printf("\n sig_int starting\n");
    for (i = 0; i < 300000; i++) {
        for (j = 0; j < 4000; j++) {
            k += i * j;
        }
    }
    printf("sig_int over\n");
}

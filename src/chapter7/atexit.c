/*
 * =====================================================================================
 *
 *       Filename:  atexit.c
 *
 *    Description:  atexitʹ����ʾ,ע��ص���������ջ����ģ���ע����ִ��
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 11ʱ21��36��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"

static void exit1(void);
static void exit2(void);

int main(int argc, const char* argv[]) {
    if (atexit(exit1) != 0) {
        err_sys("register exit1 fail");
    }

    if (atexit(exit2) != 0) {
        err_sys("register exit2 fail");
    }

    printf("main is done\n");

    // ����exit��return�򲻷��ض���ִ�лص�
    exit(0);
    //_exit(0); // ��ִ�лص���ֱ�ӽ��ں�
}

static void exit1(void) {
    printf("exit 1 handler\n");
}

static void exit2(void) {
    printf("exit 2 handler\n");
}


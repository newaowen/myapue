/*
 * =====================================================================================
 *
 *       Filename:  share_std.c
 *
 *    Description:  ���ӽ��̹���std�������������
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 21ʱ41��05��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include "stdlib.h"

int main() {
    int pid;
    int c;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        // �ӽ��̳�Ϊ��session
        if ((c = getc(stdin)) != EOF){
            printf("child get c: ");
            putc(c, stdout);
            putc('\n', stdout);
        }
        //setsid();
        exit(0);
    }

    if ((c = getc(stdin)) != EOF){
        printf("parent get c: ");
        putc(c, stdout);
        putc('\n', stdout);
    }
    exit(0);
}

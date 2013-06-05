/*
 * =====================================================================================
 *
 *       Filename:  fork_new_session.c
 *
 *    Description:  ϰ��2,��fork�½��̲����ӽ��̳�Ϊ�µ�session
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
        // ��һ���ӽ��̳�Ϊ��session��Ϊ�鳤)
        setsid();
        if ((pid = fork()) < 0) {
            err_sys("first child fork error");
        } else if (pid == 0) { // �ڶ����ӽ���,����session�з��鳤��������ն��޹���
            // �ر������� 
            for (int i = 0; i < NOFILE; i ++) {
                close(i);
            }
            // �ض������������
            // ...
        }

        exit(0);
    }

    exit(0);
}

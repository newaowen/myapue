/*
 * =====================================================================================
 *
 *       Filename:  zombie.c
 *
 *    Description:  ���ɽ�ʬ���̣�����system����ps�鿴
 *                  �������˳��󣬽�ʬ���̻ᱻinit���
 *        Version:  1.0
 *        Created:  2013��06��04�� 18ʱ57��00��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <stdlib.h>

int main() {
    int pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        printf("child start\n");
        exit(0);
    }

    // ��waitpid���ȴ��ӽ��̽���
    sleep(1);

    // �鿴�ӽ�ʬ����
    system("ps ef | grep Z");

    // ע�⣺�������˳��󣬽�ʬ���̻ᱻinit�����
}

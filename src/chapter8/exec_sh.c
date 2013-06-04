/*
 * =====================================================================================
 *
 *       Filename:  exec_sh.c
 *
 *    Description:  ��ʾ�������ļ�ִ��
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 18ʱ35��45��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execl("./test.sh", "test.sh",
            "arg1", "arg2", (char*)0) < 0) {
            err_sys("exec error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        err_sys("waitpid error");
    }
}

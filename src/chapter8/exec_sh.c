/*
 * =====================================================================================
 *
 *       Filename:  exec_sh.c
 *
 *    Description:  演示解释器文件执行
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 18时35分45秒
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

/*
 * =====================================================================================
 *
 *       Filename:  fork_new_session.c
 *
 *    Description:  习题2,　fork新进程并让子进程成为新的session
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 21时41分05秒
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
        // 第一代子进程成为新session（为组长)
        setsid();
        if ((pid = fork()) < 0) {
            err_sys("first child fork error");
        } else if (pid == 0) { // 第二代子进程,在新session中非组长，与控制终端无关联
            // 关闭描述符 
            for (int i = 0; i < NOFILE; i ++) {
                close(i);
            }
            // 重定向输入输出等
            // ...
        }

        exit(0);
    }

    exit(0);
}

/*
 * =====================================================================================
 *
 *       Filename:  zombie.c
 *
 *    Description:  生成僵尸进程，并用system调用ps查看
 *                  父进程退出后，僵尸进程会被init清除
 *        Version:  1.0
 *        Created:  2013年06月04日 18时57分00秒
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

    // 不waitpid，等待子进程结束
    sleep(1);

    // 查看子僵尸进程
    system("ps ef | grep Z");

    // 注意：父进程退出后，僵尸进程会被init清除的
}

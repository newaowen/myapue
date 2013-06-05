/*
 * =====================================================================================
 *
 *       Filename:  share_std.c
 *
 *    Description:  父子进程共享std输入输出的问题
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
        // 子进程成为新session
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

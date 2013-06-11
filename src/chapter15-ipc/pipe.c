/*
 * =====================================================================================
 *
 *       Filename:  pipe.c
 *
 *    Description:  演示管道用法
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 19时32分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"

int main() {
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    pipe(fd);
    pid = fork();
    if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello pipe\n", 12);
        printf("[parent]write to pipe...\n");
    } else {
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        printf("[child]read from pipe...\n");
        printf("%s", line);
    }
}


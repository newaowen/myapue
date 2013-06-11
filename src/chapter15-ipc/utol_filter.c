/*
 * =====================================================================================
 *
 *       Filename:  utol_filter.c
 *
 *    Description:  演示popen作为过滤输入的用法
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 19时51分26秒
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

int main() {
    char line[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("./utol", "r")) == NULL) {

    }
    for (;;) {
        fputs("prompt> ", stdout);
        // 标准输入为行缓冲，而propmt与输入要保持在同一行，因此要手动fflush立即现实'propmt>'
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL) {
            break;
        }
        if (fputs(line, stdout) == EOF) {

        }
    }
    pclose(fpin);
    putchar('\n');
}



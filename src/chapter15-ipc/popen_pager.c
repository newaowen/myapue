/*
 * =====================================================================================
 *
 *       Filename:  popen_pager.c
 *
 *    Description:  演示popen向分页程序(more|less)传文件
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 19时42分55秒
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

// 这里意思是如果shell环境变量PAGER已定义则取其值，否则使用more
#define PAGER "${PAGER:-more}"

int main(int argc, char**argv) {
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2) {
        err_quit("usage: cmd <pathname>");
    }

    fpin = fopen(argv[1], "r");
    fpout = popen(PAGER, "w");

    while (fgets(line, MAXLINE, fpin) != NULL) {
        if (fputs(line, fpout) == EOF) {
            err_sys("fputs error to pipe");
        }
    }

    ferror(fpin);
    pclose(fpout);
}


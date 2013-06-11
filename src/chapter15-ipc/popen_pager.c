/*
 * =====================================================================================
 *
 *       Filename:  popen_pager.c
 *
 *    Description:  ��ʾpopen���ҳ����(more|less)���ļ�
 *
 *        Version:  1.0
 *        Created:  2013��06��11�� 19ʱ42��55��
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

// ������˼�����shell��������PAGER�Ѷ�����ȡ��ֵ������ʹ��more
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


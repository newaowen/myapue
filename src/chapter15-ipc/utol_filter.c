/*
 * =====================================================================================
 *
 *       Filename:  utol_filter.c
 *
 *    Description:  ��ʾpopen��Ϊ����������÷�
 *
 *        Version:  1.0
 *        Created:  2013��06��11�� 19ʱ51��26��
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
        // ��׼����Ϊ�л��壬��propmt������Ҫ������ͬһ�У����Ҫ�ֶ�fflush������ʵ'propmt>'
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



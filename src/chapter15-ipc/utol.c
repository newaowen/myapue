/*
 * =====================================================================================
 *
 *       Filename:  utol.c
 *
 *    Description:  ��д����Сдת���Ĺ��˳�����ʾpopen�ô�
 *
 *        Version:  1.0
 *        Created:  2013��06��11�� 19ʱ49��24��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <ctype.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        if (isupper(c)) {
            c = tolower(c);
        }
        if (putchar(c) == EOF) {

        }
        if (c == '\n') {
            fflush(stdout);
        }
    }
}


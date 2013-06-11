/*
 * =====================================================================================
 *
 *       Filename:  utol.c
 *
 *    Description:  大写－＞小写转换的过滤程序，演示popen用处
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 19时49分24秒
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


/*
 * =====================================================================================
 *
 *       Filename:  check_endian.c
 *
 *    Description:  判断系统字节序(big endian or little endian)
 *
 *        Version:  1.0
 *        Created:  2013年06月14日 15时22分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void) {
    int a = 0x33323130;
    char* p = (char*)&a;
    printf("a(%x) in memory(from low to high): %c %c %c %c\n", a, *p, *(p+1), *(p+2), *(p+3));
    if ((*p) > *(p+1)) {
        printf("big endian\n");
    } else {
        printf("little endian\n");
    }

    return;
}

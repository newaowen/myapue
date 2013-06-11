/*
 * =====================================================================================
 *
 *       Filename:  select_sleep.c
 *
 *    Description:  ��ʾʹ��selectģ��sleep
 *
 *        Version:  1.0
 *        Created:  2013��06��11�� 16ʱ55��49��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <sys/select.h>

int main() {
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    printf("select begin\n");
    if (select(0, NULL, NULL, NULL, &tv) == -1) {
        err_sys("select error");
    }
    printf("select over\n");
}


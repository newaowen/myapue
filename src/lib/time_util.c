/*
 * =====================================================================================
 *
 *       Filename:  time_util.c
 *
 *    Description:  time工具
 *
 *        Version:  1.0
 *        Created:  2013年06月01日 21时54分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*  Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1) {
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

int timeval_subtract_micro(struct timeval *t2, struct timeval *t1) {
    struct timeval result; 
    timeval_subtract(&result, t2, t1);
    return result.tv_usec;
}

void timeval_print(struct timeval *tv, int hide_ts) {
    char buffer[30];
    time_t curtime;

    if (hide_ts != TRUE) {
        printf("(%ld.%06ld)", tv->tv_sec, tv->tv_usec);
    }
    curtime = tv->tv_sec;
    strftime(buffer, 30, "%Y-%m-%d %T", localtime(&curtime));
    printf("%s.%06ld\n", buffer, tv->tv_usec);
}

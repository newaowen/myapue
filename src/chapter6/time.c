/*
 * =====================================================================================
 *
 *       Filename:  time.c
 *
 *    Description:  演示日期时间函数
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 10时32分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <time.h>

int main(int argc, const char* argv[]) {
    time_t unixts = time(NULL);
    // localtime将日历时间转化为便于阅读的本地时间tm
    struct tm* current_time = localtime(&unixts);

    char buf[MAXLINE];
    // strftime对tm进行格式化输出
    strftime(buf, MAXLINE, "%F %T", current_time); 
    printf("local time: %s\n", buf);
    exit(0);
}

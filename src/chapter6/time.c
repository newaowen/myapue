/*
 * =====================================================================================
 *
 *       Filename:  time.c
 *
 *    Description:  ��ʾ����ʱ�亯��
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 10ʱ32��54��
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
    // localtime������ʱ��ת��Ϊ�����Ķ��ı���ʱ��tm
    struct tm* current_time = localtime(&unixts);

    char buf[MAXLINE];
    // strftime��tm���и�ʽ�����
    strftime(buf, MAXLINE, "%F %T", current_time); 
    printf("local time: %s\n", buf);
    exit(0);
}

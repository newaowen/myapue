/*
 * =====================================================================================
 *
 *       Filename:  read_environ.c
 *
 *    Description:  ��ȡȫ�ֻ�����, ����key=value���ַ�����ʽ����
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 11ʱ43��33��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"

extern char** environ;

int main(int argc, const char* argv[]) {
    printf("environ(Key=Value)\n");
    while (*environ != NULL) {
        printf("%s\n", *environ);
        environ ++;
    }     
}


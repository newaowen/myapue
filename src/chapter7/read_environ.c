/*
 * =====================================================================================
 *
 *       Filename:  read_environ.c
 *
 *    Description:  读取全局环境表, 表以key=value的字符串形式保存
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 11时43分33秒
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


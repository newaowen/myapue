/*
 * =====================================================================================
 *
 *       Filename:  ls_dir.c
 *
 *    Description:  显示目录原生内容数据, 经测试不行，open无法打开目录
 *
 *        Version:  1.0
 *        Created:  2013年06月02日 17时17分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <fcntl.h>

int main(int argc, const char* argv[]) {
    char* fileName; 
    int fd;

    if (argc != 2) {
        err_sys("usage: command filename");
    }

    // open打开目录
    fileName = argv[1];
    // open权限判断和第二个参数有关系的，O_RDONLY, O_RDWR
    // open不能打开目录
    if ((fd = open(argv[1], O_RDWR)) < 0) {
        err_ret("open file %s error", argv[1]);
    } else {
        printf("open %s ok\n", fileName);
    }

    char buf[MAXLINE]; 
    int n;
    while ((n = read(fd, buf, MAXLINE)) > 0) {
        printf("file content: %s", buf);
    } 
    
    return 0;
}


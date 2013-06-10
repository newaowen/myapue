/*
 * =====================================================================================
 *
 *       Filename:  access_test.c
 *
 *    Description:  access调用演示，设置了set_uid_bit的进程, 如果将可执行文件修改设置set_uid位,并该owner为root
 *                  切换到当前用户再次执行，open可执行，但access不行，因此set_uid_bit对access判断没有影响
 *                  例子：./access_test /etc/shadow
 *
 *        Version:  1.0
 *        Created:  2013年06月02日 16时01分10秒
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

    fileName = argv[1];
    // open权限判断和第二个参数有关系的，O_RDONLY, O_RDWR
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        err_ret("open file %s error", argv[1]);
    } else {
        printf("open %s ok\n", fileName);
    }

    if (access(argv[1], R_OK) < 0) {
        err_sys("access file error");
    } else {
        printf("access %s ok\n", fileName);
    }

    return 0;
}


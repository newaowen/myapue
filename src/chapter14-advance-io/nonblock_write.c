/*
 * =====================================================================================
 *
 *       Filename:  nonblock_write.c
 *
 *    Description:  演示非阻塞写调用, 好像没什么直接使用场景
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 10时49分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char buf[500000];

int main(void) {
    int ntowrite, nwrite;
    char *ptr;

    // 标准输入输出已打开，没必要open
    // 直接从标准输入读取数据(这里注意，遇到回车read将返回)
    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    // 设置非阻塞
    set_fl(STDOUT_FILENO, O_NONBLOCK);
    ptr = buf;
    while (ntowrite > 0) {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
        if (nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }
}


/*
 * =====================================================================================
 *
 *       Filename:  lseek_with_append.c
 *
 *    Description:  ����appendʱ�ܷ�ʹ��lseek���������Ч
 *
 *        Version:  1.0
 *        Created:  2013��06��02�� 12ʱ11��47��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
//  #include <sys/types.h>
//      #include <sys/stat.h>
#include <fcntl.h>


int main(int argc, const char* argv) {
    int n;
    int fd;
    char buf[10];
    char* fileName = "lseek_file.txt";
    if ((fd = open(fileName, O_APPEND | O_RDWR)) < 0) {
        err_sys("open file error");
    }

    // ʹ��lseekд(����������Ƶ�ĩβ��д)
    lseek(fd, 0, SEEK_SET);
    buf[0] = 'B';
    if ((n = write(fd, buf, 1)) < 0) {
        err_sys("write file error");
    }

    close(fd);
    return 0;
}


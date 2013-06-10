/*
 * =====================================================================================
 *
 *       Filename:  ls_dir.c
 *
 *    Description:  ��ʾĿ¼ԭ����������, �����Բ��У�open�޷���Ŀ¼
 *
 *        Version:  1.0
 *        Created:  2013��06��02�� 17ʱ17��10��
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

    // open��Ŀ¼
    fileName = argv[1];
    // openȨ���жϺ͵ڶ��������й�ϵ�ģ�O_RDONLY, O_RDWR
    // open���ܴ�Ŀ¼
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


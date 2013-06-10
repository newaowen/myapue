/*
 * =====================================================================================
 *
 *       Filename:  access_test.c
 *
 *    Description:  access������ʾ��������set_uid_bit�Ľ���, �������ִ���ļ��޸�����set_uidλ,����ownerΪroot
 *                  �л�����ǰ�û��ٴ�ִ�У�open��ִ�У���access���У����set_uid_bit��access�ж�û��Ӱ��
 *                  ���ӣ�./access_test /etc/shadow
 *
 *        Version:  1.0
 *        Created:  2013��06��02�� 16ʱ01��10��
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
    // openȨ���жϺ͵ڶ��������й�ϵ�ģ�O_RDONLY, O_RDWR
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


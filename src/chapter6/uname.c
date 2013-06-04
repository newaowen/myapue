/*
 * =====================================================================================
 *
 *       Filename:  uanme.c
 *
 *    Description:  ��ʾuname�ӿ�
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 10ʱ17��38��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <sys/utsname.h>

int main(int argc, const char* argv[]) {
    struct utsname buf;

    uname(&buf);
    printf("uname result: sysname %s, nodename %s, release %s, version %s, machine %s\n",
            buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
    exit(0);
}

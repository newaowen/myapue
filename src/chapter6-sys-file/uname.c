/*
 * =====================================================================================
 *
 *       Filename:  uanme.c
 *
 *    Description:  演示uname接口
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 10时17分38秒
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

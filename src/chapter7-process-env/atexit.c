/*
 * =====================================================================================
 *
 *       Filename:  atexit.c
 *
 *    Description:  atexit使用演示,注意回调函数是以栈保存的，后注册先执行
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 11时21分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"

static void exit1(void);
static void exit2(void);

int main(int argc, const char* argv[]) {
    if (atexit(exit1) != 0) {
        err_sys("register exit1 fail");
    }

    if (atexit(exit2) != 0) {
        err_sys("register exit2 fail");
    }

    printf("main is done\n");

    // 调用exit或return或不返回都会执行回调
    exit(0);
    //_exit(0); // 不执行回调，直接进内核
}

static void exit1(void) {
    printf("exit 1 handler\n");
}

static void exit2(void) {
    printf("exit 2 handler\n");
}


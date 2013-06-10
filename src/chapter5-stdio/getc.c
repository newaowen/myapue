/*
 * =====================================================================================
 *
 *       Filename:  getc.c
 *
 *    Description:  演示getc用法, 是否需要先到文件尾才能获取字符
 *
 *        Version:  1.0
 *        Created:  2013年06月03日 22时39分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include "stdio.h"

int main(int argc, const char* argv[]) {
    int c; 
    
    // 测试在行缓冲情况下getc
    // 由于stdin是行缓冲的，所以必须碰到回车\n或者文件结束符(终端是Ctrl+D)才能读取（之前是阻塞的）
    // 当为回车时立即从缓冲中循环获取字符，注意这里会把\n也读到
    // 读完\n后getc重新进入阻塞状态;当为Ctrl+D时，其实相当于起行结束的作用，但并没有在缓冲区中输入新的字符
    while ((c = getc(stdin)) != EOF) {
        printf("getchar: %c(%d)\n", c, c);
    }

    // 通过ctrl+D结束(新行输入并且之前没有输入字符)
    if (feof(stdin) != 0) {
        printf("stdin is end!\n");
    }

    return 0;
}


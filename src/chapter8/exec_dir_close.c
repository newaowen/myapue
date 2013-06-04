/*
 * =====================================================================================
 *
 *       Filename:  exec_dir_close.c
 *
 *    Description:  演示exec调用关闭目录流的情况
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 19时12分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <sys/types.h>
#include <dirent.h>

int main() {
    DIR *dir  = opendir("./");
    if (dir != NULL) {
        err_sys("opendir error");
    }

    // 打印dir的关闭标志
    // Linux下没找到DIR结构体中与close on exec相关的标志位...
    // dir->

    int pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        execlp("./show_close_on_exec", "", "", (char*)0);
    }
}


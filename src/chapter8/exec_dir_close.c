/*
 * =====================================================================================
 *
 *       Filename:  exec_dir_close.c
 *
 *    Description:  ��ʾexec���ùر�Ŀ¼�������
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 19ʱ12��21��
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

    // ��ӡdir�Ĺرձ�־
    // Linux��û�ҵ�DIR�ṹ������close on exec��صı�־λ...
    // dir->

    int pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        execlp("./show_close_on_exec", "", "", (char*)0);
    }
}


/*
 * =====================================================================================
 *
 *       Filename:  myls.c
 *
 *    Description:  ls like 
 *
 *        Version:  1.0
 *        Created:  2013-05-30 10:13:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        err_quit("usage: myls {path}");
    }

    if ((dp = opendir(argv[1])) == NULL) {
        // 系统调用发生异常
        err_sys("cannot open %s", argv[1]);
    } 
    
    while ((dirp = readdir(dp)) != NULL) {
        printf("%l%s\t\t%d\t%d\n", dirp->d_ino, dirp->d_name, dirp->d_reclen, dirp->d_type);
    }

    closedir(dp);
    exit(0);
}


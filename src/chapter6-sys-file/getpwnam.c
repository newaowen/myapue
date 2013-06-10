/*
 * =====================================================================================
 *
 *       Filename:  getpwnam.c
 *
 *    Description:  getpwnam演示
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 09时37分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <pwd.h>
#include <stddef.h>
#include <string.h>

// getpwnam的模拟实现
struct passwd* my_getpwnam(const char* name) {
    struct passwd *ptr;

    setpwent();
    while ((ptr = getpwent()) != NULL) {
        if (strcmp(name, ptr->pw_name) == 0) {
            break;
        }
    }

    endpwent();
    return ptr;
}

int main(int argc, const char* argv[]) {
    char* name = "zhanqu";
    struct passwd* pd = my_getpwnam(name);
    printf("getpwname user: %s, uid: %d\n", name, pd->pw_uid);
    return 0;
}

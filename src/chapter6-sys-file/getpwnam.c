/*
 * =====================================================================================
 *
 *       Filename:  getpwnam.c
 *
 *    Description:  getpwnam��ʾ
 *
 *        Version:  1.0
 *        Created:  2013��06��04�� 09ʱ37��51��
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

// getpwnam��ģ��ʵ��
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

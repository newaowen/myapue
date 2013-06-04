/*
 * =====================================================================================
 *
 *       Filename:  getspnam.c
 *
 *    Description:  getspnam演示, 获取阴影文件中保存的加密后的口令
 *                  注意：该文件必须具有root权限，才能读取shadow文件
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
#include <shadow.h>
#include <stddef.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    char* name = "zhanqu";
    setspent();
    struct spwd* pd = getspnam(name);
    if (pd != NULL) {
        printf("getspname user: %s, shadow passwd: %s\n", name, pd->sp_pwdp);
    } else {
        printf("getspnam error, no such name: %s", name);
    }
    endspent();
    return 0;
}

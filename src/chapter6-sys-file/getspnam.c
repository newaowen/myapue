/*
 * =====================================================================================
 *
 *       Filename:  getspnam.c
 *
 *    Description:  getspnam��ʾ, ��ȡ��Ӱ�ļ��б���ļ��ܺ�Ŀ���
 *                  ע�⣺���ļ��������rootȨ�ޣ����ܶ�ȡshadow�ļ�
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

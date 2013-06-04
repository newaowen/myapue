/*
 * =====================================================================================
 *
 *       Filename:  getc.c
 *
 *    Description:  ��ʾgetc�÷�, �Ƿ���Ҫ�ȵ��ļ�β���ܻ�ȡ�ַ�
 *
 *        Version:  1.0
 *        Created:  2013��06��03�� 22ʱ39��51��
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
    
    // �������л��������getc
    // ����stdin���л���ģ����Ա��������س�\n�����ļ�������(�ն���Ctrl+D)���ܶ�ȡ��֮ǰ�������ģ�
    // ��Ϊ�س�ʱ�����ӻ�����ѭ����ȡ�ַ���ע��������\nҲ����
    // ����\n��getc���½�������״̬;��ΪCtrl+Dʱ����ʵ�൱�����н��������ã�����û���ڻ������������µ��ַ�
    while ((c = getc(stdin)) != EOF) {
        printf("getchar: %c(%d)\n", c, c);
    }

    // ͨ��ctrl+D����(�������벢��֮ǰû�������ַ�)
    if (feof(stdin) != 0) {
        printf("stdin is end!\n");
    }

    return 0;
}


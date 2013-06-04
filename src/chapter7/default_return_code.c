/*
 * =====================================================================================
 *
 *       Filename:  default_return_code.c
 *
 *    Description:  不调用return,exit时的返回值
 *                  在shell中使用echo $? 显示上一次进程执行结果
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 16时01分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */


int main() {
    // printf的结果当作main的返回值
    printf("hello world!!!");
}

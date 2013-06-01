/**
 * 从标准输入复制到标准输出
 * 演示read, write io接口使用
 */
#include "apue.h"

#define BUFFSIZE 1024
int main(int argc, const char* argv[]) {
    int n;
    char  buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write err");
        }
    }

    if (n < 0) {
        err_sys("read err");
    }

    exit(0);
}
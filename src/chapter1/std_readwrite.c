/**
 * 使用标准io实现的复制标准输出到标准输入
 */
#include "apue.h"

int main(int argc, const char* argv[]) {
    int c;

    while ((c = getc(stdin)) != EOF) {
        printf("getc get a char %c\n", c);
        if (putc(c, stdout) == EOF) {
            err_sys("put error");
        }
    }

    if (ferror(stdin)) {
        err_sys("input error");
    }

    return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  printf_io_buffer.c
 *
 *    Description:  显示标准io的缓冲设置
 *                  执行结果：
 *                  stream = stdin, line buffered, buffer size = 1024
 *                  stream = stdout, line buffered, buffer size = 1024
 *                  stream = stderr, unbuffered, buffer size = 0
 *                  stream = file.txt, fully buffered, buffer size = 4096
 *
 *        Version:  1.0
 *        Created:  2013年06月03日 23时16分08秒
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

void print_buffer(const char* filename, FILE* file) {
    printf("stream = %s, ", filename);

    if (file->_IO_file_flags & _IO_UNBUFFERED) {
        printf("unbuffered");
    } else if (file->_IO_file_flags & _IO_LINE_BUF) {
        printf("line buffered");
    } else {
        printf("fully buffered");
    }

    printf(", buffer size = %d\n", file->_IO_buf_end - file->_IO_buf_base);
}

int main(int argc, const char* argv[]) {
    FILE *fp;
    
    // 需从流中读或写才能建立缓冲区，获取准确的默认缓冲大小,否则会获取到0
    fputs("enter to activate stdin buffer size\n", stdout);
    if (getc(stdin) == EOF) {
        err_sys("getc error");
    }

    //fputs("activate stdout\n", stderr);
    print_buffer("stdin", stdin);
    print_buffer("stdout", stdout);
    print_buffer("stderr", stderr);

    if ((fp = fopen("file.txt", "a+")) == NULL) {
        err_sys("fopen error");
    }

    // 需从流中读或写才能建立缓冲区，获取准确的默认缓冲大小
    if (putc('A', fp) == EOF) {
        err_sys("putc error");
    }
    print_buffer("file.txt", fp);
    exit(0);
}

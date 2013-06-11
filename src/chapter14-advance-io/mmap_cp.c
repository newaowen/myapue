/*
 * =====================================================================================
 *
 *       Filename:  mmap_cp.c
 *
 *    Description:  ��ʾmmap�����ļ�
 *
 *        Version:  1.0
 *        Created:  2013��06��11�� 16ʱ14��16��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char**argv) {
    int fdin, fdout;
    void *src, *dst;
    struct stat statbuf;

    if (argc != 3) {
        err_quit("usage: %s <fromfile> <tofile>", argv[0]);
    }

    fdin = open(argv[1], O_RDONLY);
    fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);

    // ��ȡ�ļ���С
    fstat(fdin, &statbuf);
    printf("stat file %s size: %d B\n", argv[1], statbuf.st_size);

    lseek(fdout, statbuf.st_size - 1, SEEK_SET);
    write(fdout, "", 1);

    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
    printf("mmap src: %p\n", src);
    dst = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, 0);
    printf("mmap dst: %p\n", dst);

    // ֱ���ڴ�������ɺܷ�����ľ��
    memcpy(dst, src, statbuf.st_size);

    // ����Ҫunmap?
    // ����ȷ���ļ�д�룬ִ��msync
}


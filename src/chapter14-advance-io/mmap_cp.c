/*
 * =====================================================================================
 *
 *       Filename:  mmap_cp.c
 *
 *    Description:  演示mmap复制文件
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 16时14分16秒
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

    // 获取文件大小
    fstat(fdin, &statbuf);
    printf("stat file %s size: %d B\n", argv[1], statbuf.st_size);

    lseek(fdout, statbuf.st_size - 1, SEEK_SET);
    write(fdout, "", 1);

    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
    printf("mmap src: %p\n", src);
    dst = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, 0);
    printf("mmap dst: %p\n", dst);

    // 直接内存操作即可很方便有木有
    memcpy(dst, src, statbuf.st_size);

    // 不需要unmap?
    // 如需确保文件写入，执行msync
}


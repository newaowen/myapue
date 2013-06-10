/*
 * =====================================================================================
 *
 *       Filename:  share_file_rw.c
 *
 *    Description:  演示父子进程共享fd,以及同时读写的情况
 *
 *        Version:  1.0
 *        Created:  2013年06月01日 19时59分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *
 * =====================================================================================
 */

#include "apue.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char* argv) {
    int pid;
    int fd;
    char buf[MAXLINE];

    // 打开文件
    char* fileName = "file.txt";

	// 细节：当O_CREAT和O_EXCL一起用时,当fileName已经存在时，open调用将失败(即返回值不是有效的fd,而是-1)
	// 且该判断是原子性的(即当有另一个进程同时创建了该文件时，这个调用也不会出错，内核保证原子性)
	// O_EXCL也只和O_CREAT一起用,其他用法结果未定义
    if ((fd = open(fileName, O_CREAT | O_EXCL | O_WRONLY,  S_IRUSR | S_IWUSR)) < 0) {
        err_sys("open file error");
    }

    // 看看fork执行时间　
	// 工作机器执行结果是：父进程先与子进程返回，但差别不大，大概500us以内
    struct timeval tvBegin, tvEnd, tvDiff;
    gettimeofday(&tvBegin, NULL);
    printf("[parent]fork at: ");
    timeval_print(&tvBegin);

    // 生成子进程
    if ((pid = fork()) < 0) { // fork失败则不会产生子进程
        err_sys("fork error");
    } else if (pid == 0) {  // 子进程
		// fork执行完后的时间显示
        gettimeofday(&tvEnd, NULL);
        printf("[child]fork time end: ");
        timeval_print(&tvEnd);
		printf("[child]fork time: %d us\n", timeval_subtract_micro(&tvEnd, &tvBegin));

		// 循环写文件
		int i = 0;
		for (i = 0; i < 5; i++) {
			buf[0] = 'C';
			int n = write(fd, buf, 2);
			printf("[child]\twrite file size %d \n", n);
			usleep(1000*100);
		}
        printf("[child]\ti'm exiting\n");
        exit(0);
    }
        
    // fork一般先返回到父进程，然后再返回到子进程执行
    gettimeofday(&tvEnd, NULL);
    printf("[parent]fork time end: ");
    timeval_print(&tvEnd);

	printf("[parent]fork time: %d us\n", timeval_subtract_micro(&tvEnd, &tvBegin));
    // 注意：写文件时没必要在字符串后面加0,加0是在内存中，运行时判断字符串结尾的!
    // buf[1] = 0;
    // 父进程写文件,fork需要一些时间，因此一般父进程先执行到这
    // 因此加个sleep循环就有意思了
	// 这种情况下写文件操作相互错乱了，必须加锁控制才行!!
	int i = 0;
	for (i = 0; i < 5; i++) {
		buf[0] = 'P';
		int n = write(fd, buf, 2);
		printf("parent write file size %d \n", n);
		usleep(1000*100);
	}
    close(fd);

    //　等待子进程结束
    wait(NULL);
    printf("wait over, child has dead --!\n");
    exit(0);
}

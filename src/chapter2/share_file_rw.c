/*
 * =====================================================================================
 *
 *       Filename:  share_file_rw.c
 *
 *    Description:  ��ʾ���ӽ��̹���fd,�Լ�ͬʱ��д�����
 *
 *        Version:  1.0
 *        Created:  2013��06��01�� 19ʱ59��07��
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

    // ���ļ�
    char* fileName = "file.txt";

	// ϸ�ڣ���O_CREAT��O_EXCLһ����ʱ,��fileName�Ѿ�����ʱ��open���ý�ʧ��(������ֵ������Ч��fd,����-1)
	// �Ҹ��ж���ԭ���Ե�(��������һ������ͬʱ�����˸��ļ�ʱ���������Ҳ��������ں˱�֤ԭ����)
	// O_EXCLҲֻ��O_CREATһ����,�����÷����δ����
    if ((fd = open(fileName, O_CREAT | O_EXCL | O_WRONLY,  S_IRUSR | S_IWUSR)) < 0) {
        err_sys("open file error");
    }

    // ����forkִ��ʱ�䡡
	// ��������ִ�н���ǣ������������ӽ��̷��أ�����𲻴󣬴��500us����
    struct timeval tvBegin, tvEnd, tvDiff;
    gettimeofday(&tvBegin, NULL);
    printf("[parent]fork at: ");
    timeval_print(&tvBegin);

    // �����ӽ���
    if ((pid = fork()) < 0) { // forkʧ���򲻻�����ӽ���
        err_sys("fork error");
    } else if (pid == 0) {  // �ӽ���
		// forkִ������ʱ����ʾ
        gettimeofday(&tvEnd, NULL);
        printf("[child]fork time end: ");
        timeval_print(&tvEnd);
		printf("[child]fork time: %d us\n", timeval_subtract_micro(&tvEnd, &tvBegin));

		// ѭ��д�ļ�
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
        
    // forkһ���ȷ��ص������̣�Ȼ���ٷ��ص��ӽ���ִ��
    gettimeofday(&tvEnd, NULL);
    printf("[parent]fork time end: ");
    timeval_print(&tvEnd);

	printf("[parent]fork time: %d us\n", timeval_subtract_micro(&tvEnd, &tvBegin));
    // ע�⣺д�ļ�ʱû��Ҫ���ַ��������0,��0�����ڴ��У�����ʱ�ж��ַ�����β��!
    // buf[1] = 0;
    // ������д�ļ�,fork��ҪһЩʱ�䣬���һ�㸸������ִ�е���
    // ��˼Ӹ�sleepѭ��������˼��
	// ���������д�ļ������໥�����ˣ�����������Ʋ���!!
	int i = 0;
	for (i = 0; i < 5; i++) {
		buf[0] = 'P';
		int n = write(fd, buf, 2);
		printf("parent write file size %d \n", n);
		usleep(1000*100);
	}
    close(fd);

    //���ȴ��ӽ��̽���
    wait(NULL);
    printf("wait over, child has dead --!\n");
    exit(0);
}

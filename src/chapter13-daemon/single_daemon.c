/*
 * =====================================================================================
 *
 *       Filename:  single_daemon.c
 *
 *    Description:  ��ʵ���ػ�����
 *
 *        Version:  1.0
 *        Created:  2013��06��10�� 16ʱ11��02��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/resource.h>

#define LOCKFILE "/var/run/single_daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

extern int errno;
extern int lockfile(int);

/* 
 * ����ļ��Ƿ�����
 */
int lockfile(int fd) {
    struct flock fk;
    fk.l_type = F_WRLCK;
    fk.l_start = 0;
    fk.l_whence = SEEK_SET;
    fk.l_len = 0;
    return (fcntl(fd, F_SETLK, &fk));
}

/*
 * ����ػ������Ƿ��Ѿ�����
 */
int already_running() {
    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if (fd < 0) {
        syslog(LOG_ERR, "cannt open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    } else {
        printf("open lockfile fail\n");
    }

    // ע������LOCK_NBΪ�������ģ�δ��ȡ��ʱ���س���
    // Ϊʲôlockfile������������������������ʵ����Ȼ���Լ���
    if (lockfile(fd) < 0) {
        printf("lock file fali, maybe daemon has already run?\n");
        if (errno == EACCES || error == EAGAIN) {
            close(fd);
        }
        syslog(LOG_ERR, "cannot lock %s, %s" , LOCKFILE, strerror(errno));
        exit(1);
    } else {
        printf("lock file success\n");
    }

    printf("start daemon\n");
    // ���ļ���д��pid
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);
}

void daemonize(const char* cmd) {
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    // ��մ����ļ�mask
    umask(0);

    if ((pid = fork()) < 0) {
        err_quit("cannot fork");
    } else if (pid != 0) {
        printf("[parent]exit\n");
        exit(0);
    }

    // ����Ҫ�����뵱ǰ�����ն�
    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGHUP, &sa, NULL);

    if ((pid = fork()) < 0) {
        err_quit("cannot fork 2", cmd);
    } else if (pid != 0) {
        printf("[child]exit\n");
        exit(0);
    }

    // change pwd
    chdir("/");

    // �ر��ļ�������
    getrlimit(RLIMIT_NOFILE, &rl);
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }
    for (i = 3; i < rl.rlim_max; i++) {
        close(i);
    }

    // ��֤��һʵ��
    // ������ǰ��Ĺر���������ִ��, ���ض����׼ioǰִ��
    printf("check file lock\n");
    already_running();
  
    // 0, 1, 2�ض���/dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // ��ϵͳ��־�ļ�
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    // ����ubuntu��־·�� /var/log/syslog
    syslog(LOG_INFO, "daemon started");
}

int main() {
    daemonize("simple daemon");
    // �������ߡ�
    sleep(1000000);
}


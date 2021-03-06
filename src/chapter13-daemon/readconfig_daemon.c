/*
 * =====================================================================================
 *
 *       Filename:  readconfig_daemon.c
 *
 *    Description:  支持运行时重新读取配置的守护进程
 *
 *        Version:  1.0
 *        Created:  2013年06月10日 17时12分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <syslog.h>
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

#define LOCKFILE "/var/run/readconfig_daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

/* 
 * 检测文件是否被锁定
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
 * 检测守护进程是否已经运行
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

    // 注意设置LOCK_NB为非阻塞的，未获取锁时返回出错
    // 为什么lockfile不能上锁？？？　其他进程实例仍然可以加锁
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
    // 向文件中写入pid
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);
}

void daemonize(const char* cmd) {
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    // 清空创建文件mask
    umask(0);

    if ((pid = fork()) < 0) {
        err_quit("cannot fork");
    } else if (pid != 0) {
        printf("[parent]exit\n");
        exit(0);
    }

    // 很重要，脱离当前控制终端
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

    // 关闭文件描述符
    getrlimit(RLIMIT_NOFILE, &rl);
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }
    for (i = 3; i < rl.rlim_max; i++) {
        close(i);
    }

    // 保证单一实例
    // 必须在前面的关闭描述符后执行, 在重定向标准io前执行
    printf("check file lock\n");
    already_running();
  
    // 0, 1, 2重定向到/dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // 打开系统日志文件
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    // 本机ubuntu日志路径 /var/log/syslog
    syslog(LOG_INFO, "daemon started");
}

void reread() {
    // 重新加载配置
    
    // 不可重入的　
}

void sigterm(int signo) {
    syslog(LOG_INFO, "sigterm catched, exit");
    exit(0);
}

void sighup(int signo) {
    syslog(LOG_INFO, "reread conf in");
    reread();
    syslog(LOG_INFO, "reread conf out, return from sig handler");
}

int main() {
    struct sigaction sa;

    daemonize("reaconfig");
    already_running();

    // 处理sigterm信号 (kill -15 pid)
    sa.sa_handler = sigterm;
    sigemptyset(&sa.sa_mask);
    // 屏蔽SIGHUP
    sigaddset(&sa.sa_mask, SIGHUP);
    sa.sa_flags = 0;
    sigaction(SIGTERM, &sa, NULL);

    // HUP信号处理 (kill -1 pid)
    sa.sa_handler = sighup;
    sigemptyset(&sa.sa_mask);
    // 屏蔽SIGTERM
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;
    sigaction(SIGHUP, &sa, NULL);

    // sleep 不是信号可重入的？
    // 注意，sleep在进程接受到非忽略的信号后将立即返回
    sleep(100000);
    /* 
    while (1) {
        syslog(LOG_INFO, "getc wait");
        //getc(stdin);
    }
    */
}

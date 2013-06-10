/*
 * =====================================================================================
 *
 *       Filename:  daemon_login.c
 *
 *    Description:  测试守护进程是否可以获取登陆用户名
 *
 *        Version:  1.0
 *        Created:  2013年06月10日 21时39分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

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
    for (i = 0; i < rl.rlim_max; i++) {
        close(i);
    }
    // 0, 1, 2重定向到/dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // 打开系统日志文件
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    printf("[daemon]openlog\n");
    // 本机ubuntu日志路径 /var/log/syslog
    syslog(LOG_INFO, "daemon started");
}

int main() {
    daemonize("simple daemon");

    // getlogin返回空指针
    char * user = getlogin();
    syslog(LOG_INFO, "daemon login user: %s", user);
    // 进入休眠　
    sleep(10000);
}



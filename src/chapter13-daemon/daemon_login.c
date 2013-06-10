/*
 * =====================================================================================
 *
 *       Filename:  daemon_login.c
 *
 *    Description:  �����ػ������Ƿ���Ի�ȡ��½�û���
 *
 *        Version:  1.0
 *        Created:  2013��06��10�� 21ʱ39��23��
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
    for (i = 0; i < rl.rlim_max; i++) {
        close(i);
    }
    // 0, 1, 2�ض���/dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // ��ϵͳ��־�ļ�
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    printf("[daemon]openlog\n");
    // ����ubuntu��־·�� /var/log/syslog
    syslog(LOG_INFO, "daemon started");
}

int main() {
    daemonize("simple daemon");

    // getlogin���ؿ�ָ��
    char * user = getlogin();
    syslog(LOG_INFO, "daemon login user: %s", user);
    // �������ߡ�
    sleep(10000);
}



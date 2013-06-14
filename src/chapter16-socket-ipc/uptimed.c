/*
 * =====================================================================================
 *
 *       Filename:  uptime.c
 *
 *    Description:  面向连接的服务器uptime
 *
 *        Version:  1.0
 *        Created:  2013年06月12日 23时53分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <error.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/socket.h>

#define BUFLEN 128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif 

void init_hint_addr(struct addrinfo* hint) {
    memset(hint, 0, sizeof(struct addrinfo));
    hint->ai_flags = AI_CANONNAME;
    hint->ai_socktype = SOCK_STREAM;
    hint->ai_family = 0;
    hint->ai_protocol = 0;
    hint->ai_addrlen = 0;
    hint->ai_canonname = NULL;
    hint->ai_addr = NULL;
    hint->ai_next = NULL;
}

// 初始化服务
int init_server(int type, struct sockaddr* addr, socklen_t alen, int qlen) {
    int fd;
    int err = 0;

    if ((fd = socket(addr->sa_family, type, 0)) < 0) {

    }
    if (bind(fd, addr, alen) < 0) {
        err = errno;
        goto errout;
    }

    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(fd, qlen) < 0) {
            err = errno;
            goto errout;
        }
    }
    return fd;

errout:
    close(fd);
    errno = err;
    err_sys("init server");
    return -1;
}

// 实际服务程序
void serve(int sockfd) {
    int clfd;
    FILE *fp;
    char buf[BUFLEN];

    // 循环服务
    for (;;) {
        clfd = accept(sockfd, NULL, NULL);
        if (clfd < 0) {
            exit(1);
        }
        
        if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
            // 出错
            sprintf(buf, "error: %s", strerror(errno));
            // 发送错误信息给客户端
            send(clfd, buf, strlen(buf), 0);
        } else {
            // 打开uptime成功，从fd中获取数据
            while (fgets(buf, BUFLEN, fp) != NULL) {
                send(clfd, buf, strlen(buf), 0);
                syslog(LOG_INFO, "send to client: %s\n", buf);
            }
            pclose(fp);
        }
    }
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

    /*  
    // 关闭文件描述符
    getrlimit(RLIMIT_NOFILE, &rl);
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }
    for (i = 3; i < rl.rlim_max; i++) {
        close(i);
    }
    */

    // 保证单一实例
    // 必须在前面的关闭描述符后执行, 在重定向标准io前执行
    //printf("check file lock\n");
  
    // 0, 1, 2重定向到/dev/null
    //fd0 = open("/dev/null", O_RDWR);
    //fd1 = dup(0);
    //fd2 = dup(0);

    // 打开系统日志文件
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    // 本机ubuntu日志路径 /var/log/syslog
    syslog(LOG_INFO, "daemon started");
}


int main(int argc, char** argv) {
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err, n;
    char *host;

    if (argc != 1) {
        err_quit("usage: ruptimed");
    }

    n = HOST_NAME_MAX;
    host = malloc(n);
    if (host == NULL) {
        err_sys("malloc error");
    }
    gethostname(host, n);

    //变为守护进程 
    daemonize("ruptimed");

    printf("gethost: %s\n", host);

    // 初始化addrinfo hint
    printf("init addrinfo hint\n");
    init_hint_addr(&hint);

    if ((err = getaddrinfo(host, "uptimed", &hint, &ailist)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(-1);
    }
    printf("getaddrinfo (uptimed):%s \n", ailist->ai_addr);
     
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        printf("init server at %s\n", aip->ai_addr);
        sockfd = init_server(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN);
        printf("serve at sock %d", sockfd);
        serve(sockfd);
        exit(0);
    }
}


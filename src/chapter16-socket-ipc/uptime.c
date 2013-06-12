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
#include <sys/socket.h>

#define BUFLEN 128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif 

int init_server(int sockfd, struct sockaddr* addr, socklen_t len, int flag) {

}

void serve(int sockfd) {
    int clfd;
    FILE *fp;
    char buf[BUFLEN];

    for (;;) {
        clfd = accept(sockfd, NULL, NULL);
        if (clfd < 0) {
            exit(1);
        }
        
        if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
            sprintf(buf, "error: %s", strerror(errno));
            send(clfd, buf, strlen(buf), 0);
        } else {
            while (fgets(buf, BUFLEN, fp) != NULL) {
                send(clfd, buf, strlen(buf), 0);
            }
            pclose(fp);
        }
    }
}

int main(int argc, char** argv) {
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;

    if (argc != 1) {
        err_quit("usage: ruptimed");
    }

    //变为守护进程 
    daemonize("ruptimed");

    init_hint_addr(&hint);

    if ((err = getaddrinfo(host, "ruptime", &hint, &aip)) == NULL) {

    }

    for (api = ailist; aip != NULL; aip = aip->next) {
        sockfd = init_server(SOCKET_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN);
        serve(sockfd);
        exit(0);
    }
}


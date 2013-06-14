/*
 * =====================================================================================
 *
 *       Filename:  get_uptime.c
 *
 *    Description:  ��ʾͨ��socket��ȡuptime���������, ʹ�ã�./ruptime localhost
 *
 *        Version:  1.0
 *        Created:  2013��06��12�� 23ʱ36��58��
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
#include <sys/socket.h>

#define MAXSLEEP 128
#define MAXADDRLEN 256
#define BUFLEN  128

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen) {
    int nsec;

    for (nsec = 1; nsec <= MAXSLEEP; nsec <<= 1) {
        if (connect(sockfd, addr, alen) == 0) {
            return 0;
        }
        if (nsec <= MAXSLEEP/2) {
            sleep(nsec);
        }
    }

    return -1;
}


void print_uptime(int sockfd) {
    int n;
    char buf[BUFLEN];

    while ((n = recv(sockfd, buf, BUFLEN, 0)) >0) {
        write(STDOUT_FILENO, buf, n);
    }
}

int main(int argc, char** argv) {
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;

    if (argc != 2) {
        err_quit("usage: ruptime hostname");
    }

    hint.ai_flags = 0;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if ((err = getaddrinfo(argv[1], "uptimed", &hint, &ailist)) != 0) {
        err_quit("getaddrinfo error");
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        sockfd = socket(aip->ai_family, SOCK_STREAM, 0);

        connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen);
        print_uptime(sockfd);
    }
}



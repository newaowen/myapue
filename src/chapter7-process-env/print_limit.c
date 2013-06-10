/*
 * =====================================================================================
 *
 *       Filename:  print_limit.c
 *
 *    Description:  打印进程资源限制
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 15时39分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#if defined(BSD) || defined(MACOS)
#include <sys/time.h>
#define FMT "%10lld  "
#else
#define FMT "%10ld  "
#endif

#include <sys/resource.h>

#define doit(name) pr_limits(#name, name)

static void pr_limits(char*, int);

int main(void) {
#ifdef RLIMT_AS
        doit(RLIMIT_AS);
#endif
        doit(RLIMIT_CORE);
        doit(RLIMIT_CPU);
        doit(RLIMIT_DATA);
        doit(RLIMIT_FSIZE);

#ifdef RLIMIT_LOCKS
        doit(RLIMIT_LOCKS);
#endif

#ifdef RLIMIT_MEMLOCKS
        doit(RLIMIT_MEMLOCK);
#endif
        doit(RLIMIT_NOFILE);
#ifdef RLIMIT_NPROC
        doit(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_RSS
        doit(RLIMIT_RSS);
#endif

#ifdef RLIMIT_SBSIZE
        doit(RLIMIT_SBSIZE);
#endif
        doit(RLIMIT_STACK);

#ifdef RLIMIT_VMEM
        doit(RLIMIT_VMEM);
#endif
}

static void pr_limits(char* name, int res) {
    struct rlimit limit;

    if (getrlimit(res, &limit) < 0) {
        err_sys("getrlimit error");
    }

    printf("%-14s  ", name);
    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite) ");
    } else {
        printf(FMT, limit.rlim_cur);
    }

    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite) ");
    } else {
        printf(FMT, limit.rlim_max);
    }
    putchar((int)'\n');
}

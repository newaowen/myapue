/*
 * =====================================================================================
 *
 *       Filename:  print_shm.c
 *
 *    Description:  打印进程各存储区大致地址范围
 *
 *        Version:  1.0
 *        Created:  2013年06月12日 17时38分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <sys/shm.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600

char array[ARRAY_SIZE];
char p = 'p';

int main(void) {
    int shmid;
    char *ptr, *shmptr;

    printf("inited global data %p\n", &p);
    // 非初始化数据区
    printf("array[] from %p to %p\n", &array[0], &array[ARRAY_SIZE]);
    printf("stack around %p\n", &shmid);

    ptr = malloc(MALLOC_SIZE);
    printf("malloced from %p to %p\n", ptr, ptr + MALLOC_SIZE);

    shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE);
    shmptr = shmat(shmid, 0, 0);
    printf("shared memory[%d] attached from %p to %p\n", shmid, shmptr, shmptr + SHM_SIZE);

    // 删除共享存储区(如不调用，通过ipcs命令可以查看到)
    shmctl(shmid, IPC_RMID, 0);
}


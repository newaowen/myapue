/*
 * =====================================================================================
 *
 *       Filename:  cmd_jmp.c
 *
 *    Description:  命令行处理的典型程序骨架
 *
 *        Version:  1.0
 *        Created:  2013年06月04日 15时20分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aowen (newaowen@yahoo.com.cn), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "apue.h"
#include <setjmp.h>

#define TOK_ADD 5

void do_line(char*);
void cmd_add(void);
int get_token(void);

jmp_buf jmpbuffer;

int main(void) {
    char line[MAXLINE];

    if (setjmp(jmpbuffer) != 0) {
        printf("error");
    }

    while (fgets(line, MAXLINE, stdin) != NULL) {
        do_line(line);
    }

    exit(0);
}

char *tok_ptr;

void do_line(char* ptr) {
    int cmd;

    tok_ptr = ptr;
    while ((cmd = get_token()) > 0) {
        switch(cmd) {
            case TOK_ADD:
                cmd_add();
                break;
        }
    }
}

void cmd_add(void) {
    int token;
    token = get_token();
    
    if (token < 0) {
        longjmp(jmpbuffer, 1);
    }
    // process command
}

int get_token(void) {
    // fetch next token from line
}

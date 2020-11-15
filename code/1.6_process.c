// 1.6_process.c
// 一个简单的shell程序

#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
    char        buf[MAXLINE];      // MAXLINE is max line length
    pid_t       pid;
    int         status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf)-1] == '\n')    // replace \n with \0
            buf[strlen(buf)-1] = 0;
        
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);                     // 127 -- command not found
        }
    }

}

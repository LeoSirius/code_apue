// 1.6_process.c
// 用子进程执行命令来实现一个简单的shell程序。只能执行简单的命令，不能有参数

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
        if (buf[strlen(buf)-1] == '\n')    // replace \n with \0, 因为fgets返回的以\n结尾
            buf[strlen(buf)-1] = 0;
        
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);   // exec会用新的程序替换子进程
            err_ret("couldn't execute: %s", buf);
            exit(127);                     // 127 -- command not found
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}

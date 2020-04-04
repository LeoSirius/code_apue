/*
 * DESC:
 * 在进程管理中加入信号。自定义信号处理函数来处理SIGINT信号
 * 
 * NOTES:
 * signal(int signum, sighandler_t handler)会把signum的处理绑定到handler上
 * 
 * 一个进程处理信号有三种方式：
 * 1. 忽略不管。这样可能引起硬件异常
 * 2. 触发默认行为。如除0的默认行为是终止进程。
 * 3. 自定义信号处理函数
 */
#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);    /* 自定义的信号处理函数 */

int
main(void)
{
    char buf[MAXLINE];      /* form apue.h */
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}

void
sig_int(int signo)
{
    printf("interrupt\n%% ");
}

/*
 * NOTES:
 * 这个程序fork子进程，并返回不同的状态给父进程
 * 
 * 返回状态可以作用于三个宏。
 * WIFEXITED    正常退出
 * WIFSIGNALED  异常退出
 * WIFSTOPPED   停止
 * 
 */

#include "apue.h"
#include <sys/wait.h>

void
pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
            WTERMSIG(status),
#ifdef WCORDUMP
            WCOREDUMP(status) ? " (core file generated)" : "");
#else
            "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int
main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)          /* child process */
        exit(7);

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);            /* print status */


    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)          /* child process */
        abort();
    
    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);            /* print status */


    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)          /* child process */
        status /= 0;            /* divide by 0 generates SIGFPE */
    
    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);            /* print status */

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// normal termination, exit status = 7
// abnormal termination, signal number = 6
// abnormal termination, signal number = 8
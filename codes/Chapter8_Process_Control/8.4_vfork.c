/*
 * NOTES:
 * vfork()不同于fork()之处：
 * 1. 子进程使用父进程的地址空间。（所以最后父进程中的输出，值也加了1）
 * 2. 子进程先执行，再子进程调用exit或exec后，父进程再继续
 */

#include "apue.h"

int globvar = 6;

int
main(void)
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        globvar++;
        var++;
        _exit(0);           /* child process terminates */
    }

    /* print in parent process */
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// before vfork
// pid = 4563, glob = 7, var = 89
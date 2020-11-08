/*
 * NOTES:
 * 注意两种输出的情况
 * write是没有buffer的，直接输出
 * printf如果输出在终端上，则是行buffer，换行符清空的buffer，所以只输出了一次
 * printf没有关联终端，则是完全buffer，在fork的时候，buffer也被复制了，所以输出了两次
 * 
 * 另外fork之后，进程表中的文件描述符也被复制了，所以重定向输出，父进程和子进程输出的是一个地方
 */

#include "apue.h"

int globvar = 6;
char buf[] = "a write to stdout\n";

int
main(void)
{
    int var;
    pid_t pid;

    var = 88;
    /* 注意sizeof和strlen的区别，后者会自动去除最后的null。sizeof是在编译时完成计算的 */
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
        err_sys("write error");
    printf("before fork\n");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {  /* child process */
        globvar++;
        var++;
    } else {                /* parent process */
        sleep(2);
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// a write to stdout
// before fork
// pid = 4096, glob = 7, var = 89
// pid = 4095, glob = 6, var = 88

// leo@ubuntu:~/c_test$ ./a.out > tmpout
// leo@ubuntu:~/c_test$ cat tmpout 
// a write to stdout
// before fork
// pid = 4098, glob = 7, var = 89
// before fork
// pid = 4097, glob = 6, var = 88
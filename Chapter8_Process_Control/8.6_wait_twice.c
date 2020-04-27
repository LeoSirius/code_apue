/*
 * NOTES:
 * 一个进程在terminate后，父进程wait之前，称之为僵尸进程
 * 如果我们既不想在父进程中wait，又要避免僵尸进程。可以fork两次。
 * 
 * 子进程exit掉，孙进程没有父进程，其父进程会变成init。
 */

#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {       /* first child */
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)      /* parent of second child */
            exit(0);           /* exit first child */
        
        sleep(2);       /* 等一会，让first child终止掉，其父进程变成init */
        printf("second child, parent pid = %ld\n", (long)getpid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)       /* wait for first child */
        err_sys("waitpid error");

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// leo@ubuntu:~/c_test$ second child, parent pid = 4245
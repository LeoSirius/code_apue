/*
 * DESC:
 * 进程控制
 * 
 * NOTES:
 * 进程控制的系统调用包括：
 * - fork
 * - exec, exec有7种变型，统称为exec
 * - waitpid
 * 
 * fgets()读入的字符串以换行符结尾，但是execlp需要一个普通的NULL结尾的字符串
 * 所以这里做了一个转换
 * 
 * fork() is called once - by parent - but return twice - in parent and child.
 * exec 会用一个新的program file来替换fork复制出来的子进程
 * 注意execlp第一个参数是程序名，第二个参数才是要执行的程序的argv[0]，所以这里buf占了两个参数
 */

#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
    char buf[MAXLINE];  /* MAXLINE is from apue.h */
    pid_t pid;
    int status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;          /* replace newline with null */
        
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {                  /* child */
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}
/* 
 * DESC:
 * input content from std input, then output it to stdout.
 * i.g. copy file from stdin to stdout
 * 
 * NOTES:
 * 系统调用的IO函数时unbuffered的，即需要手动创建buffer。
 * 而标准库的IO函数的buffered，不需要手动开辟buffer。见1.5stdio.c
 */
#include "apue.h"

#define BUFFSIZE 4096

int
main(void)
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");

    if (n < 0)
        err_sys("read error");

    exit(0);
}

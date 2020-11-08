/* 
 * DESC:
 * 使用标准IO库来实现copy文件
 * 
 * NOTES:
 * 标准IO函数不同于系统调用IO函数，不需要手动开辟buffer
 */

#include "apue.h"

int
main(void)
{
    int c;

    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            err_sys("output error");

    if (ferror(stdin))
        err_sys("input error");

    exit(0);
}
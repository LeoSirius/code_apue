// 1.5_copy2.c
// 用标准库拷贝文件，getc和putc一次读写一个字符。
// 这两个函数的参数是文件流，而不是文件描述符
#include "apue.h"

int
main(void)
{
    int       c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            err_sys("output error");
    if (ferror(stdin))
        err_sys("input error");

    exit(0);
}
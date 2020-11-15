// 1.5_copy.c
// 用 system call 和 对标准输入输出的重定向，实现文件拷贝
#include "apue.h"

#define BUFFSIZE 4096

int
main(void)
{
    int     n;
    char    buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)   // 当读到EOF时，read返回0
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
    
    if (n < 0)
        err_sys("read error");
    
    exit(0);
}
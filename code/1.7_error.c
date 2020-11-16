// 1.7_error.c
// 展示两个错误处理函数

#include "apue.h"
#include <errno.h>

int
main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;                                         // No such file or directory
    perror(argv[0]);
    exit(0);
}

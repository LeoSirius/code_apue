/*
 * DESC:
 * 
 * NOTES:
 * strerror()根据传入的errno返回描述字符串
 * perror()则根据当前errno值直接向标准错误输出描述字符串
 */
#include "apue.h"
#include <errno.h>

int
main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));  /* EACCES: Permission denied */
    errno = ENOENT;                                     /* ENOENT: No such file or directory */
    perror(argv[0]);
    exit(0);
}
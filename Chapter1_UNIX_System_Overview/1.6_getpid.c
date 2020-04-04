/*
 * DESC:
 * getpid() 返回当前进程的pid
 */
 #include "apue.h"

int
main(void)
{
    printf("Hello world from process ID %ld\n", (long)getpid());
    exit(0);
}

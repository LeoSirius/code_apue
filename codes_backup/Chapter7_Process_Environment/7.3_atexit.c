/*
 * NOTES:
 * 内核要执行一个程序，只能调用exec()函数。一个程序要主动结束，只能是用_exit()或_Exit()
 * exit()会在执行exit handlers和关闭io流后，调用_exit()或_Exit()。
 * _exit()和_Exit()会立即返回kernel，不会做其他事情
 * 
 * atexit()可以添加exit handler函数，调用的顺序和添加的顺序相反。
 * exit handler函数没有参数和返回值
 * 
 * main函数中return (0) 等价于 exit(0)
 */

#include "apue.h"

static void my_exit1(void);
static void my_exit2(void);

int
main(void)
{
    if (atexit(my_exit2) != 0)
        err_sys("can't register my_exit2");

    if (atexit(my_exit1) != 0)
        err_sys("can't register my_exit1");
    if (atexit(my_exit1) != 0)
        err_sys("can't register my_exit1");

    printf("main is done\n");
    return (0);
}

static void
my_exit1(void)
{
    printf("first exit handle\n");
}

static void
my_exit2(void)
{
    printf("second exit handler\n");
}

// 实际执行顺序与注册顺序相反
// leo@ubuntu:~/c_test$ ./a.out 
// main is done
// first exit handle
// first exit handle
// second exit handler
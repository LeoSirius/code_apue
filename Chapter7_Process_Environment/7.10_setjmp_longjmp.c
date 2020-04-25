/*
 * NOTES:
 * gcc -O选项对编译的内容进行优化
 * volatile - 不对变量进行优化
 * register - 对变量进行寄存器优化
 * 
 * setjmp()函数设置跳回点
 * longjmp()跳回跳回点
 * 在调用longjmp，栈中多余的函数会被抛弃掉。
 * 调用longjmp后，内存中的变量会保持调用longjmp时的值
 * 而寄存器中的变量会退回到调用setjmp时的值
 * 
 * 如果要让值是longjmp后的值，最好把变量声明为volatile，保证了其是存在内存中的
 * 
 * setjmp第一次调用时返回0，调用longjmp时，第二个参数就是跳转回setjmp时的返回值
 */

#include "apue.h"
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);

static jmp_buf jmpbuffer;
static int     globval;

int
main(void)
{
    int autoval;
    register int regival;
    volatile int volaval;
    static int statval;

    globval = 1, autoval = 2, regival = 3, volaval = 4, statval = 5;

    if (setjmp(jmpbuffer) != 0) {
        printf("after longjmp:\n");
        printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
            globval, autoval, regival, volaval, statval);
        exit(0);
    }

    /* change value after setjmp, before longjmp */
    globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99;
    f1(autoval, regival, volaval, statval);
    exit(0);
}

static void
f1(int i, int j, int k, int l)
{
    printf("in f1():\n");
    printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
        globval, i, j, k, l);
    f2();
}

static void
f2(void)
{
    longjmp(jmpbuffer, 1);
}

// leo@ubuntu:~/c_test$ gcc t.c -lapue
// leo@ubuntu:~/c_test$ ./a.out 
// in f1():
// globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
// after longjmp:
// globval = 95, autoval = 96, regival = 3, volaval = 98, statval = 99

// 优化编译后，autoval也存在了寄存器中，所以值也退回去了
// leo@ubuntu:~/c_test$ gcc t.c -O -lapue
// leo@ubuntu:~/c_test$ ./a.out 
// in f1():
// globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99
// after longjmp:
// globval = 95, autoval = 2, regival = 3, volaval = 98, statval = 99
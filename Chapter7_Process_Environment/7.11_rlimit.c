#include "apue.h"
#include <sys/resource.h>

/* 
 * #是取字符串的意思
 * 这样定义doit宏，编译器会把
 * doit(RLIMIT_CORE)
 * 解释为
 * pr_limits("RLIMIT_CORE", RLIMIT_CORE)
 */
#define doit(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main()
{
#ifdef RLIMIT_AS
    doit(RLIMIT_AS);
#endif

    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);

#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
    doit(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
    doit(RLIMIT_NICE);
#endif

#ifdef RLIMIT_NOFILE
    doit(RLIMIT_NOFILE);
#endif

#ifdef RLIMIT_NPROC
    doit(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS);
#endif

#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif

#ifdef RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
    doit(RLIMIT_SIGPENDING);
#endif

#ifdef RLIMIT_STACK
    doit(RLIMIT_STACK);
#endif

#ifdef RLIMIT_SWAP
    doit(RLIMIT_SWAP);
#endif

#ifdef RLIMIT_VMEM
    doit(RLIMIT_VMEM);
#endif

    exit(0);
}

static void
pr_limits(char *name, int resource)
{
    struct rlimit limit;
    unsigned long long lim;

    if (getrlimit(resource, &limit) < 0)
        err_sys("getrlimit error for %s", name);
    printf("%-20s  ", name);

    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite)  ");
    } else {
        lim = limit.rlim_cur;
        printf("%10lld  ", lim);
    }

    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)");
    } else {
        lim = limit.rlim_max;
        printf("%10lld  ", lim);
    }
    putchar((int)'\n');
}


// leo@ubuntu:~/c_test$ ./a.out 
// RLIMIT_AS             (infinite)  (infinite)
// RLIMIT_CORE                    0  (infinite)
// RLIMIT_CPU            (infinite)  (infinite)
// RLIMIT_DATA           (infinite)  (infinite)
// RLIMIT_FSIZE          (infinite)  (infinite)
// RLIMIT_MEMLOCK          16777216    16777216  
// RLIMIT_MSGQUEUE           819200      819200  
// RLIMIT_NICE                    0           0  
// RLIMIT_NOFILE               1024     1048576  
// RLIMIT_NPROC                7651        7651  
// RLIMIT_RSS            (infinite)  (infinite)
// RLIMIT_SIGPENDING           7651        7651  
// RLIMIT_STACK             8388608  (infinite)

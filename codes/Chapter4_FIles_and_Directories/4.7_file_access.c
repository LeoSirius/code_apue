/*
 * NOTES:
 * access用于检查当前real-uid，而不是effective-uid
 * 当把文件的set-user-id位turn on的时候，effective-uid会变成文件所有者的uid，而不是real-uid
 * access函数可以检查的是real-uid，而不是进程中的effectie-uid
 */

#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        err_quit("usage: a.out <pathname>");

    if (access(argv[1], R_OK) < 0)
        err_ret("access error for %s", argv[1]);
    else
        printf("read access OK\n");

    if (open(argv[1], O_RDONLY) < 0)
        err_ret("open error for %s", argv[1]);
    else
        printf("open for reading OK\n");

    exit(0);
}

// real-id和effective-uid都不行。（这时real-uid和effective-uid应该是一样的）
// leo@ubuntu:~/c_test$ ./a.out /etc/shadow
// access error for /etc/shadow: Permission denied   
// open error for /etc/shadow: Permission denied

// leo@ubuntu:~/c_test$ sudo chown root a.out
// leo@ubuntu:~/c_test$ sudo chmod u+s a.out


// x的位置变成s，表示当该程序执行时，set-user-id打开，以文件所有者的id执行
// leo@ubuntu:~/c_test$ ll a.out 
// -rwsrwxr-x 1 root leo 13280 Apr 15 05:50 a.out*

// 这时real-uid是当前用户，而effective-uid是文件所有者，即root
// leo@ubuntu:~/c_test$ ./a.out /etc/shadow
// access error for /etc/shadow: Permission denied
// open for reading OK
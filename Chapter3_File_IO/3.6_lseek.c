/*
 * DESC:
 * 测试一个文件是否支持seek
 * 
 * NOTES:
 * 如果lseek的fd参数的文件是不支持seek，则会返回-1。pipe，FIFO，socket等文件是不支持seek的
 * lseek只会修改内核中的offset数据，不会引起IO操作
 */

#include "apue.h"

int
main(void)
{
    off_t t;
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out < /etc/passwd
// seek OK
// leo@ubuntu:~/c_test$ cat < /etc/passwd | ./a.out 
// cannot seek

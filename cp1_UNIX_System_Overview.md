# Chapter1 UNIX System Overview

## 1.2 UNIX Architecture

狭义上的操作系统只包括内核，其需要完成两个核心功能：

1. 向下管理硬件
2. 向上提供程序运行的环境

## 1.3 Loggin in

### Logging Name

`/etc/passwd`文件记录了用户的信息。下面是一个例子

```
leo:x:1000:1000::/home/leo:/bin/sh
```

冒号分隔开了一共七列，分别是：`用户名`、`密码（用x填充）`、`用户id`、`群组id`、`家目录`、`shell程序`

## 1.4 Files and Directories

```cpp
// 1.4_ls.c
// 用库函数实现ls命令
#include "apue.h"
#include <dirent.h>

int
main(int argc, char *argv[])
{
    DIR             *dp;          // DIR 类似于 FILE，是指向目录的结构体
    struct dirent   *dirp;        // 存放目下的dirent的结构体

    if (argc != 2)
        err_quit("usage: ls directort_name");
    if ((dp = opendir(argv[1])) == NULL)
        err_sys("can't open %s", argv[1]);
    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);

    closedir(dp);
    exit(0);
}
```

## 1.5 Input and Output

- 系统调用IO：unbuffered io，需要另外手动开辟buffer
- 标准库IO：buffered io，无需另外手动开辟buffer

首先用系统调用来实现文件拷贝

```cpp
// 1.5_copy1.c
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
```

这个程序有两个用法。可以直接在程序运行时通过shell进行标准输出。也可以重定向标准输入。

```
$ ./a.out
aaa EOF
aaa   # 这是输出
```

```
(base) root code (master) # echo hello > outfile
(base) root code (master) # ./a.out < outfile > infile
(base) root code (master) # cat infile 
hello
```

用标准库来实现拷贝

```cpp
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
```

## 1.6 Programs and Processes

操作进程的三个函数：

- fork
- exec（family）
- waitpid

```cpp
// 1.6_process.c
// 用子进程执行命令来实现一个简单的shell程序。只能执行简单的命令，不能有参数

#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
    char        buf[MAXLINE];      // MAXLINE is max line length
    pid_t       pid;
    int         status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf)-1] == '\n')    // replace \n with \0, 因为fgets返回的以\n结尾
            buf[strlen(buf)-1] = 0;
        
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);   // exec会用新的程序替换子进程
            err_ret("couldn't execute: %s", buf);
            exit(127);                     // 127 -- command not found
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}
```

## 1.7 Error Handling

两个处理error的函数

- `char *strerror(int errno);     // <string.h>`，返回errno对应的字符串
- `void perror(const char *msg);  // <stdio.h>`，会向stderr输出`"msg" + ": " + errno对应的字符串 + "\n"`

```cpp
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
```

```
(base) root test (master) # ./a.out 
EACCES: Permission denied
./a.out: No such file or directory
```

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



```c
#include "apue.h"
#include <dirent.h>

int
main(int argc, char *argv[])
{
    DIR             *dp;
    struct dirent   *dirp;

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




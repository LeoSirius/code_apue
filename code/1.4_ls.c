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
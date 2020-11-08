/*
 * DESC:
 * 
 * NOTES:
 * lstat不同于stat之处在于，lstat会显示symlink，而stat会跨过symlink
 * 然后用sys/stat.h中的S_ISXXX宏来判断文件的类型
 */

#include "apue.h"

int
main(int argc, char *argv[])
{
    int i;
    struct stat buf;
    char *ptr;

    for (i = 1; i < argc; ++i) {
        printf("%s: ", argv[i]);
        if (lstat(argv[i], &buf) < 0) {
            err_ret("lstat error");
            continue;
        }
        if (S_ISREG(buf.st_mode))
            ptr = "regular";
        else if (S_ISDIR(buf.st_mode))
            ptr = "directory";
        else if (S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if (S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if (S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";
        else
            ptr = "** unknown mode **";
        printf("%s\n", ptr);
    }
    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out /etc/passwd /etc /dev/log /dev/tty /dev/sr0 /dev/cdrom 
// /etc/passwd: regular
// /etc: directory
// /dev/log: symbolic link
// /dev/tty: character special
// /dev/sr0: block special
// /dev/cdrom: symbolic link

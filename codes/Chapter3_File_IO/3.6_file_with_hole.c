/*
 * DESC:
 * file with hole
 * 
 * NOTES:
 * 注意offset是可以大于file size的，这样会创建一个有洞的文件。
 * 文件的洞不会存在磁盘上（即不会占用磁盘的block），但是read文件时，洞会被读成0。
 * 最后创建了一个同样16394大小但是没有洞的文件file.nohole。这个文件占了20个block。
 * 但是file.hole只占了8个block
 */

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefgjij";
char buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat error");
    
    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    /* offset now = 10 */

    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    /* offset now = 16384 */

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    /* offset now = 16394 */

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// leo@ubuntu:~/c_test$ ls -l file.hole 
// -rw-r--r-- 1 leo leo 16394 Apr  6 01:06 file.hole
// leo@ubuntu:~/c_test$ od -c file.hole 
// 0000000   a   b   c   d   e   f   g   j   i   j  \0  \0  \0  \0  \0  \0
// 0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
// *
// 0040000   A   B   C   D   E   F   G   H   I   J
// 0040012
// leo@ubuntu:~/c_test$ ls -ls file.hole file.nohole 
//  8 -rw-r--r-- 1 leo leo 16394 Apr  6 01:06 file.hole
// 20 -rw-rw-r-- 1 leo leo 16394 Apr  6 01:14 file.nohole
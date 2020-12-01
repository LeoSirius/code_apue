# File IO

## 3.2 File Descriptors

对内核来说，打开的文件都用文件描述符来表示。open和create文件的时候，内核会返回一个文件描述符给进程用。

除了进程级别的文件描述符，操作系统还维护了一个`打开文件表`。文件偏移量等是存在`打开文件表`里的。

![fd](https://images-of-leosirius.oss-cn-beijing.aliyuncs.com/tuchuang-tutorials/tutorial_apue/cp3_fd.png)

- A进程的fd1和30指向了同一个文件句柄（23），这可能是调用`dup`,`fcntl`或对同一文件多次`open`造成
- A进程和B进程各自的fd2指向同一个文件句柄（73），可能的情况是：
  - B从A中fork()而来
  - 通过UNIX套接字把文件描述符传给另一个进程
  - A和B`open`同一个文件，正好进程内部的fd也相同
- A的fd0和B的fd3最后指向的文件句柄不同，但是最后的inode相同，即还是同一个文件。这时两个进程操作文件的offset是不同的。

可以看到offset是系统级的。如果两个fd指向同一个文件句柄，则它们的offset是共享的。


## 3.3 open and openat Functions

openat比open多个一个文件描述符参数，根据第二个路径参数，可能有三种情况

- path是绝对路径，这时fd参数被忽略。openat和open效果一样
- path是相对路径，fd会作为相对路径的起点。
- path是相对路径，但是fd有`AT_FDCWD`。这时openat会以CWD为相对的起点。即和open一样。

> 统一进程下的不同线程的CWD是一样的。加入openat的一个目的是为了解决不同线程操作文件方便。

## 3.4 create Function

调用create其实和下面的open是等价的

```c
open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
```

## 3.5 close Function

在进程退出的时候，其打开的所有文件都会自动关闭。

## 3.6 lseek Function

### lseek的三种情况

每个打开的文件都会有一个`current file offset`，表示从文件开头到当前操作的字节的距离。

lseek根据第三个参数会有三种情况:

- SEEK_CUR，相对于当前offset
- SEEK_SET，相对于开头
- SEEK_END，相对于结尾。

一个用法是获取当前的offset

```cpp
off_t currpos;
currpos = lseek(fd, 0, SEEK_CUR);
```

对于FIFO，pipe，socket等文件是无法lseek的，这时会返回-1。这样可以判断这个文件是否是seekable。

```cpp
#include "apue.h"

int
main(void)
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");
    exit(0);
}
```

下面第二个是管道，不能seek

```
(base) root test (master) # ./a.out < /etc/passwd
seek OK
(base) root test (master) # cat < /etc/passwd | ./a.out 
cannot seek
```

### 带洞的文件

如果把offset移到文件最大字节的后面，再写东西，则可以创建有洞的文件。

```cpp
#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    // offset now = 10

    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    // offset now = 16384

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    // ofset now = 16394

    exit(0);
}
```

可以看到文件最后的大小是16394字节。用`od -c`可以看到字符内容

```
(base) root test (master) # ls -ls file.hole 
8 -rw-r--r-- 1 root root 16394 Nov 19 08:38 file.hole
(base) root test (master) # od -c file.hole 
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
*
0040000   A   B   C   D   E   F   G   H   I   J
0040012
```

用dd创建一个没有洞的文件，可以看到两个文件虽然大小是一样的。但是`file.hole`只占8个磁盘块，而`file.nohole`占了20个。

```
(base) root test (master) # dd if=/dev/zero of=file.nohole bs=16394 count=1
1+0 records in
1+0 records out
16394 bytes (16 kB, 16 KiB) copied, 0.000648582 s, 25.3 MB/s
(base) root test (master) # ls -ls file.hole file.nohole 
 8 -rw-r--r-- 1 root root 16394 Nov 19 08:38 file.hole
20 -rw-r--r-- 1 root root 16394 Nov 19 08:41 file.nohole
```

### 

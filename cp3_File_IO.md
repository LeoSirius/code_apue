# File IO

## 3.2 File Descriptors

对内核来说，打开的文件都用文件描述符来表示。open和create文件的时候，内核会返回一个文件描述符给进程用。

## 3.3 `open` and `openat` Functions

openat比open多个一个文件描述符参数，根据第二个路径参数，可能有三种情况

- path是绝对路径，这时fd参数被忽略。openat和open效果一样
- path是相对路径，fd会作为相对路径的起点。
- path是相对路径，但是fd有`AT_FDCWD`。这时openat会以CWD为相对的起点。即和open一样。

> 统一进程下的不同线程的CWD是一样的。加入openat的一个目的是为了解决不同线程操作文件方便。

## 3.4 `create` Function

调用create其实和下面的open是等价的

```c
open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
```
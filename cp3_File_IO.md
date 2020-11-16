# File IO

## 3.2 File Descriptors

对内核来说，打开的文件都用文件描述符来表示。open和create文件的时候，内核会返回一个文件描述符给进程用。

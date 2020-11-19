#include "apue.h"
#include <unistd.h>
#include <fcntl.h>

// fork -> open -> lseek
// open -> fork -> lseek
// open -> lseek -> fork

int
main(void)
{
    int fd;
    pid_t pid;
    int fd;
    off_t offset;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0) {
        // parent 
        if ((fd = open("tmp", O_CREAT, S_IRWXU) == -1))
            err_sys("open error");
        offset = lseek(fd, 10, SEEK_SET);   // set offset = 10 in parent

        off_t curroff = lseek(fd, 0, SEEK_CUR);
        // print currnet offset
        printf("in parent fd = %d, curroff = %d\n")
        

    } else {
        // child
        if ((fd = open("tmp", O_CREAT, S_IRWXU) == -1))
            err_sys("open error");
    }

    exit(0);
}
#include <fcntl.h>
#include <sys/stat.h>

#include "../tlpi.h"

int main()
{
    int fd = open("hello", O_WRONLY | O_TRUNC | O_CREAT, rwrwrw);
    write(fd, "hello", 5);
    lseek(fd, 1000000, SEEK_END);
    printf("%ld\n", write(fd, " world", 7));
    lseek(fd, 50000, SEEK_END);
    printf("%ld\n", write(fd, ".", 1));
    if (close(fd) == -1)
        err_exit(true, "close");
    exit(EXIT_SUCCESS);
}
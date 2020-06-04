#include "../tlpi.h"
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd = open("ex5.2.c", O_WRONLY | O_APPEND);
    if(fd == -1) err_exit(true, "open");

    lseek(fd, 0, SEEK_SET);
    if(write(fd, "// Where am i?\n", 15) == -1) err_exit(true, "write");

    close(fd);
    exit(EXIT_SUCCESS);
}// Where am i?

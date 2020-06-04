#include "../tlpi.h"
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char *filename = "tmp";
    int fd1, fd2, fd3;
    fd1 = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    fd2 = dup(fd1);
    fd3 = open(filename, O_RDWR);

    write(fd1, "Hello,", 6);
    write(fd2, "world", 5);
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "HELLO,", 6);
    write(fd3, "Gidday", 6);
}
#include "../tlpi.h"
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd1 = open("ex5.5.c", O_RDONLY);
    int fd2 = dup(fd1);
    lseek(fd1, 20, SEEK_SET);
    int offset = lseek(fd2, 0, SEEK_CUR);
    int stat1 = fcntl(fd1, F_GETFL);
    int stat2 = fcntl(fd2, F_GETFL);
    if (offset == 20)
        printf("OFFSET Yes\n");
    if ((stat1 ^ stat2) == 0)
        printf("STATUS Yes\n");
    exit(EXIT_SUCCESS);
}
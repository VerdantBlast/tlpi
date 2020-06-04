#include "../tlpi.h"
#include <fcntl.h>
#include <sys/stat.h>

int sdup(int oldfd)
{
    return fcntl(oldfd, F_DUPFD, 0);
}

int sdup2(int oldfd, int newfd)
{
    int fd = fcntl(oldfd, F_GETFL);
    if (fd == -1)
        err_exit(true, "fcntl getfl");
    else if (oldfd == newfd)
        return oldfd;
    else
    {
        close(newfd);
        return fcntl(oldfd, F_DUPFD, newfd);
    }
}

int main()
{
    int stdoutnew1 = sdup(STDOUT_FILENO);
    printf("Dup STDOUT: %d\n", stdoutnew1);
    if (write(stdoutnew1, "dup() work\n", 11) == -1)
        err_exit(true, "write");
    int stdoutnew2 = sdup2(STDOUT_FILENO, 0);
    if (write(0, "dup2() work\n", 12) == -1)
        err_exit(true, "write");
    if (close(stdoutnew1) == -1)
        err_exit(true, "close");
    if (close(stdoutnew2) == -1)
        err_exit(true, "close");
    exit(EXIT_SUCCESS);
}
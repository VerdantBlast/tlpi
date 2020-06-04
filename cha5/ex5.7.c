// No test

#include "../tlpi.h"
#include <fcntl.h>
#include <sys/stat.h>

struct siovec
{
    void *iov_base;
    size_t iov_len;
};

ssize_t sreadv(int fd, struct siovec *iov, int iovcnt)
{
    if (iovcnt <= 0)
        return -1;
    ssize_t total_length = 0;
    for (int i = 0; i < iovcnt; ++i)
        total_length += iov[i].iov_len;
    char *readall = (char *)malloc(total_length * sizeof(char));
    memset(readall, 0, total_length);

    if (read(fd, readall, total_length) == -1)
        err_exit(true, "read");

    size_t current_read = 0;
    for (int i = 0; i < iovcnt; ++i)
    {
        memcpy(iov[i].iov_base + current_read, readall, iov[i].iov_len);
        current_read += iov[i].iov_len;
    }
    free(readall);
    return total_length;
}

ssize_t swritev(int fd, const struct siovec *iov, int iovcnt)
{
    if (iovcnt <= 0)
        return -1;
    size_t total_length = 0;
    for (int i = 0; i < iovcnt; ++i)
        total_length += iov[i].iov_len;
    char *writeall = (char *)malloc(total_length * sizeof(char));
    memset(writeall, 0, total_length);
    size_t current_read = 0;
    for (int i = 0; i < iovcnt; ++i)
    {
        memcpy(writeall + current_read, iov[i].iov_base, iov[i].iov_len);
        current_read += iov[i].iov_len;
    }
    if (write(fd, writeall, total_length) == -1)
        err_exit(true, "write");
    free(writeall);
    return total_length;
}

int main()
{
}
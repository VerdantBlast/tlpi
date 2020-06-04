#include "../tlpi.h"

#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-h") == 0)
        usage_err("%s oldfile newfile\n", argv[0]);
    int read_num;

    int fdin = open(argv[1], O_RDONLY);
    if (fdin == -1)
        err_exit(true, "open");

    int open_flags = O_CREAT | O_TRUNC | O_WRONLY;
    int fdout = open(argv[2], open_flags, rwrwrw);
    if (fdout == -1)
        err_exit(true, "open");

    char buf;
    while ((read_num = read(fdin, &buf, 1)) > 0)
    {
        if (buf == '\0')
        {
            lseek(fdout, 1, SEEK_CUR);
            continue;
        }
        if (write(fdout, &buf, read_num) != read_num)
            err_exit(true, "write");
    }
    switch (read_num)
    {
    case -1:
        err_exit(true, "read");
    case 0:
        if (close(fdin) == -1)
            err_exit(true, "close");
        if (close(fdout) == -1)
            err_exit(true, "close");
        exit(EXIT_SUCCESS);
    }
}
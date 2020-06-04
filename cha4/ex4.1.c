#include "../tlpi.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt;
    bool is_append;
    char *filename;
    while ((opt = getopt(argc, argv, ":a")) != -1)
    {
        switch (opt)
        {
        case 'a':
            is_append = true;
            break;

        default:
            usage_err("%s [-a] filename\n", argv[0]);
        }
    }
    filename = argv[optind];

    int open_flag = O_WRONLY | O_CREAT | (is_append ? O_APPEND : O_TRUNC);
    int file_perms = rwrwrw;
    int fd = open(filename, open_flag, file_perms);
    if (fd == -1)
        err_exit(true, "open");

    char buf[512];
    int read_num;
    while ((read_num = read(STDIN_FILENO, buf, 512)) > 0)
        if (write(STDOUT_FILENO, buf, read_num) != read_num || write(fd, buf, read_num) != read_num)
            err_exit(true, "write");
    switch (read_num)
    {
    case -1:
        err_exit(true, "read");
    case 0:
        if (close(fd) == -1)
            err_exit(true, "close");
        exit(EXIT_SUCCESS);
    }
}

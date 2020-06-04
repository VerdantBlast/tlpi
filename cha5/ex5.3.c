/* > ./a.out f1 1000000 & ./a.out f1 1000000
 * > ./a.out f2 1000000 x & ./a.out f2 1000000 x
 * > ls -l
 * -rw-r--r-- 1 xxx xxx      1275374 Jun  4 08:09 f1
 * -rw-r--r-- 1 xxx xxx      1999998 Jun  4 08:10 f2
 */

#include "../tlpi.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc < 3 || strcmp(argv[1], "-h") == 0)
        usage_err("%s filename num-bytes [x]\n", argv[0]);
    bool is_append = false;
    if (argc == 4 && strcmp(argv[3], "x") == 0)
        is_append = true;
    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);

    int fd = open(filename, O_CREAT | O_WRONLY | (is_append ? O_APPEND : 0), rwrwrw);
    if (fd == -1)
        err_exit(true, "open");
    int i = -num_bytes;
    while (++i)
    {
        if (!is_append)
            lseek(fd, 0, SEEK_END);
        if (write(fd, "a", 1) == -1)
            err_exit(true, "write");
    }

    if (close(fd) == -1)
        err_exit(true, "close");

    exit(EXIT_SUCCESS);
}
/* > gcc -m32 ex5.1.c -o ex51
 *
 * > ./ex51 x 199900000000
 *
 * -rw-r--r-- 1 xxx xxx 199900000003 Jun  3 23:03 x
 */

#define _FILE_OFFSET_BITS 64
#include "../tlpi.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-h") == 0)
        usage_err("%s filename offset\n", argv[0]);
    char *filename = argv[1];
    off_t offset = atoll(argv[2]);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, rwrwrw);
    if (fd == -1)
        err_exit(true, "open");

    if (lseek(fd, offset, SEEK_SET) == -1)
        err_exit(true, "lseek");
    if (write(fd, "...", 3) == -1)
        err_exit(true, "write");

    if (close(fd) == -1)
        err_exit(true, "close");

    exit(EXIT_SUCCESS);
}
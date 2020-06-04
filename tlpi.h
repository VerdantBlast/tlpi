#ifndef _TLPI_H_
#define _TLPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "ename.c.inc"

typedef enum {
    false,
    true
} bool;

#define rwrwrw S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

#define max(a, b) ((a) < (b) ? (b) : (a))
#define min(a, b) ((a) < (b) ? (a) : (b))

static void terminte(bool use_exit)
{
    char *s;
    s = getenv("EF_DUMPCORE");
    if (s != NULL && s != "\0")
        abort();
    else if (use_exit)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

static void output_error(bool use_err, int err, bool flush_stdout, const char *format, va_list ap)
{
#define BUF_SIZE 512
    char usr_msg[BUF_SIZE], err_text[BUF_SIZE], buf[2*BUF_SIZE+7];
    vsnprintf(usr_msg, BUF_SIZE, format, ap);
    if (use_err)
        snprintf(err_text, BUF_SIZE, "[%s %s]", (err > 0 && err <= MAX_ENAME) ? ename[err] : "UNKNOWN", strerror(err));
    else
        snprintf(err_text, BUF_SIZE, ":");
    snprintf(buf, 2*BUF_SIZE+7, "Error%s %s\n", err_text, usr_msg);

    if (flush_stdout)
        fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
#undef BUF_SIZE
}

void err_msg(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    output_error(true, errno, true, format, ap);
    va_end(ap);
}

void err_exit(bool E, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    output_error(true, errno, E, format, ap);
    va_end(ap);

    terminte(E);
}

void err_exit_en(int errnum, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    output_error(true, errnum, true, format, ap);
    va_end(ap);

    terminte(true);
}

void fatal(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    output_error(false, 0, true, format, ap);
    va_end(ap);

    terminte(true);
}

void usage_err(const char *format, ...)
{
    va_list ap;
    fflush(stdout);
    fprintf(stderr, "Usage: ");
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

void cmd_err(const char *format, ...)
{
    va_list ap;
    fflush(stdout);
    fprintf(stderr, "CommandLine usage error: ");
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

#endif
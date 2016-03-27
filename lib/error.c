#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include "error.h"

#define MAX_BUF_SIZE 512

char ebuff[MAX_BUF_SIZE];

void
err_sb(const char *fun, const char *format, ...)
{
    va_list list;
    (void) snprintf(ebuff,MAX_BUF_SIZE, "%s(): ", fun);
    va_start(list, format);
    vsnprintf(ebuff + strlen(fun) + 4, MAX_BUF_SIZE, format, list);
    va_end(list);
}

void
err_sscb(const char *fun, const char *syscall)
{
    (void) snprintf(ebuff, MAX_BUF_SIZE, "%s(): %s() : (%d, %s)", fun, syscall,
                    errno, strerror(errno));
}

void
err_pb(FILE *os)
{
    fprintf(os, "%s\n", ebuff);
}



/*
    libuhp is a library dedicated to hole punching NAT traversal over UDP
    Copyright (C) <2016>  <Franck Rupin franck@holepuncher.io>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


    <libuhp>  Copyright (C) <2016>  <Franck Rupin>
    This program comes with ABSOLUTELY NO WARRANTY.
    This is free software, and you are welcome to redistribute it
    under certain conditions.
*/

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




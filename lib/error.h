#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>


void
err_sb(const char*, const char*, ...);

void
err_sscb(const char*, const char*);

void
err_pb(FILE*);

#endif /* ERROR_H */

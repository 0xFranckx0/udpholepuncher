#ifndef UHP_H
#define UHP_H

#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>

#include "error.h"
#include "svr_ux.h"

int uhp_new();
void uhp_print();

#endif /* UHP_H_ */

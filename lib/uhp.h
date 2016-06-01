#ifndef UHP_H
#define UHP_H

#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>

#include "error.h"

#define UHPPORT	4000
int run_udp();
int run_ux();

#endif /* UHP_H_ */

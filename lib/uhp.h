#ifndef UHP_H
#define UHP_H

#include <stdint.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <jansson.h>

#include "error.h"

#define UHPPORT	4000

#define KEEPALIVE_TAG   "KEEP_ALIVE"
#define HELLO_TAG       "HELLO"
#define ACK_TAG         "ACK"
#define BYE_TAG         "BYE"

enum{
	KEEPALIVE,
	HELLO,
	ACK,
	BYE
};

struct hdr_pkt{
	int	id;
	union{ 
		char 		*msg;
		struct hello_pl *hpl;
		struct ack_pl   *apl;
		struct bye_pl	*bpl;
	}pl;
};

struct hello_pl{
        char            tag[6];
        uint32_t        rand;
        time_t          timestamp;
};

struct ack_pl;
struct bye_pl;

struct hdr_pkt  *new_keepalive();
struct hdr_pkt  *new_hello();
struct hdr_pkt  *new_ack();
struct hdr_pkt  *new_bye();
void            free_pkt(struct hdr_pkt*);

json_t          *pkt2json(struct hdr_pkt*);
struct hdr_pkt  *json2pkt(json_t*);
void            read_pkt(struct hdr_pkt*);

int             run_udp();
int             run_ux();

#endif /* UHP_H */

#ifndef UHP_H
#define UHP_H

#include <stdint.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <jansson.h>
#include <event2/listener.h>
	
#include "error.h"

#define UHPPORT	4000

#define HELLO_TAG	"HELLO"
#define ACK_TAG		"ACK"

enum socket_flag{
	SERVER,
	CLIENT
};

enum msg_flag{
	HELLO,
	ACK
};

struct hdr_pkt{
	int	id;
	union{
		struct hello_pl *hpl;
		struct ack_pl   *apl;
		}pl;
};

struct hello_pl{
	char		tag[6];
	uint32_t	rand;
	time_t		timestamp;
};

struct ack_pl;

struct hdr_pkt	*new_hello();
struct hdr_pkt	*new_ack();
void		free_pkt(struct hdr_pkt*);
json_t		*pkt2json(struct hdr_pkt*);
struct hdr_pkt	*json2pkt(json_t*);
void		read_pkt(struct hdr_pkt*);


int		run_udp(evutil_socket_t,evutil_socket_t);
evutil_socket_t	new_client_socket(const char *, const char*);
evutil_socket_t	new_server_socket(const char*);

#endif /* UHP_H */

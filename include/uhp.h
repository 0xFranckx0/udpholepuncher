#ifndef UHP_H
#define UHP_H

#include <stdint.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <jansson.h>
#include <event2/listener.h>

#include "queue.h"
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

struct uhp_socks {
	char *rport;
	char *dst;
	int   r;
};

struct uhp_state {
	int 			 count;
	int 			 del;
	uint32_t 		 number;
	struct uhp_socks 	*s;
};

struct address {
	SLIST_ENTRY(address)	entry;
	int	sock;	
};
SLIST_HEAD(address_list, address);

/**
 * \struct hdr_pkt
 * \brief hdr_pkt is a header packet datastructure which is used to carry 
 *        payload used in the master election protocol and to hole punch the
 *	  the NAT.
 */
struct hdr_pkt {
	int	id;
	union{
		struct hello_pl *hpl;
		struct ack_pl   *apl;
		}pl;
};

struct base {
	uint32_t	 rand;
	time_t		 timestamp;
	char 		*port;
};

struct hello_pl {
	char		 tag[6];
	struct base 	*b;
};

struct ack_pl {
	char	 	 tag[3];
	int		 id_src;
	struct base 	*b;
	union {
		struct base	*ori;
		uint8_t		 master;
	}d;
};

struct uhp_info {
	int 	sock;
	char 	*port;
	char 	*dst;
	uint8_t master;
};

struct hdr_pkt		*new_hello(struct uhp_socks*);
struct hdr_pkt		*new_ack();
void			 free_pkt(struct hdr_pkt*);
json_t			*pkt2json(struct hdr_pkt*);
struct hdr_pkt		*json2pkt(json_t*);
void			 read_pkt(struct hdr_pkt*);

struct address_list	*init_uhp(struct uhp_socks*);
int			 run_udp(struct uhp_socks*, const char* );

evutil_socket_t		 new_sender_socket(const char *, const char*);
evutil_socket_t		 new_receiver_socket(const char*);

unsigned char		*get_addr(const char *, const int);
void 			 print_addr(const unsigned char*, const int);
#endif /* UHP_H */

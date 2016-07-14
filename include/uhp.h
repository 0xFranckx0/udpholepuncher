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

/**
 * \enum msg_flag
 * \brief Message flags 
 *
 */
enum msg_flag{
	HELLO,	/*!< HELLO Flag for hello_pl */
	ACK 	/*!< ACK Flag for ack_pl */
};

/**
 * \struct uhp_socks
 * \brief uhp_socks is used for sockets and sendto operations.
 *
 */
struct uhp_socks {
	char *rport;	/*!< receiver port */
	char *dst; 	/*!< Destination address */
	int   r; 	/*!< Socket */
};

/**
 * \struct uhp_state
 * \brief uhp_state is used during the punch hole step to get the state of the
 *	  attemtps and if the socket successfuls to strike.
 *
 */
struct uhp_state {
	int 			 count;	/*!< Number of max tries */
	int 			 del;	/*!< Del indicates whether 
						an event should be deleted */
	uint32_t 		 number;/*!< Rand number for master election */
	struct uhp_socks 	*s;	/*!< Datastructure on which previous 
					     params are applied to*/
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
	int	id;/*!< Numeric ID of HEADER packet */

	union{
		struct hello_pl *hpl;	/*!< HELLO payload */
		struct ack_pl   *apl;	/*!< ACK Payload */
		}pl;
};

/**
 * \struct base
 * \brief base struct is used into payloads. It provides the following 
 *	  informations.
 *
 */
struct base {
	uint32_t	 rand;		/*!< Random number */
	time_t		 timestamp;	/*!< Timestamp */
	char 		*port;		/*!< Original port */

};

/**
 * \struct hello_pl
 * \brief hello_pl struct is used into hdr_pkt struct. It is the first packet
 *	  of the punch.
 *
 */
struct hello_pl {
	char		 tag[6];	/*!< TAG identifying the payload */
	struct base 	*b;		/*!< Base carried by the payload */
};

/**
 * \struct ack_pl
 * \brief ack_pl struct is used into hdr_pkt struct. It is a response packet.
 *
 */
struct ack_pl {
	int		 type;		/*!< ACK Type */
	char	 	 tag[3];	/*!< ACK Tag */
	int		 id_src;	/*!< Refer to the Previous ID Header */
	struct base 	*b;		/*!< Base */
	union {
		struct base	*ori;	/*!< Original base */
		uint8_t		 master;/*!< Defines a master */
	} d;
};

/**
 * \struct uhp_info
 * \brief uhp_info is the struct returned by libuhp to the caller program once
 *	  a NAT was punched and provides informations about socket, master role
 *	  and the port to reach.
 *
 */
struct uhp_info {
	int 	 	 sock;	/*!< Socket on which communication is enabled */
	char 		*port;	/*!< Destination port */
	char 		*dst;	/*!< Destination address */
	uint8_t  	 master;/*!< Defines a master */

};

struct base		*new_base(char*);
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


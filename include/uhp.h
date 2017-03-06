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

#include "error.h"
#include "punch.h"
#include "queue.h"

#define UHPPORT	4000

#define HELLO_TAG	"HELLO"
#define ACK_TAG		"ACK"
#define BYE_TAG		"BYE"

#define RANGE	5

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
	BYE 	/*!< BYE Flag for bye_pl */
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

/**
 * \struct hdr_pkt
 * \brief hdr_pkt is a header packet datastructure which is used to carry 
 *        payload used in the master election protocol and to hole punch the
 *	  the NAT.
 */
struct hdr_pkt {
	int	transaction;/*!< Numeric ID of transaction */
	int	packet_type;
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
	unsigned char	*rand;		/*!< Random number */
	int		 timestamp;	/*!< Timestamp */
};

/**
 * \struct hello_pl
 * \brief hello_pl struct is used into hdr_pkt struct. It is the first packet
 *	  of the punch.
 *
 */
struct hello_msg {
	char		 tag[6];	/*!< TAG identifying the payload */
	int	         transaction;/*!< Numeric ID of transaction */
	unsigned char	*rand;		/*!< Random number */
	int		 timestamp;	/*!< Timestamp */
	uint8_t		 master;        /*!< Defines a master */
};

/**
 * \struct ack_pl
 * \brief ack_pl struct is used into hdr_pkt struct. It is a response packet.
 *
 */
struct ack_msg {
	int	         transaction;/*!< Numeric ID of transaction */
	int	 	 status;	/*!< msg flag */
	uint8_t		 master;        /*!< Defines a master */
	unsigned char	*rand;		/*!< Random number */
	int		 timestamp;	/*!< Timestamp */
};

struct transaction {
        uint8_t         originator:1;
        uint8_t         master:1;
        int             status;
        int             punchid;
        int             timestamp;
        char           *ip_peer;
        int             port_peer;
        uint8_t         asymetric:1;
        int             retry;
}

/* uhp_data.c */
json_t			*new_hello(struct uhp_socks *);
void			 free_hello(json_t *);
json_t			*new_ack(void);
void			 free_ack(json_t *);
json_t			*new_bye(void);
void			 free_bye(json_t *);
void			 free_message(json_t *);

/* uhp_net.c */
evutil_socket_t		 new_receiver_socket(const char *);
struct sockaddr_in 	*get_sockaddr_in(const char *, const char *);
unsigned char		*get_addr(const char *, const int);
void 			 print_addr(const unsigned char *, const int);

#endif /* UHP_H */

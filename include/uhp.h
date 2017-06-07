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

#include <event2/event.h>
#include <stdint.h>
#include <jansson.h>

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
	ACK, 	/*!< ACK Flag for ack_pl */
	BYE 	/*!< BYE Flag for bye_pl */
};

/**
 * \struct uhp_socks
 * \brief uhp_socks is used for sockets and sendto operations.
 *
 */
struct uhp_socks {
	int   r; 	/*!< Socket */
	char *rport;	/*!< receiver port */
	char *dst; 	/*!< Destination address */
};

/**
 * \struct uhp_state
 * \brief uhp_state is used during the punch hole step to get the state of the
 *	  attemtps and if the socket successfuls to strike.
 *
 */
struct uhp_state {
	struct uhp_socks 	*s;	/*!< Datastructure on which previous 
					     params are applied to*/
	int 			 count;	/*!< Number of max tries */
	int 			 del;	/*!< Del indicates whether 
						an event should be deleted */
	uint32_t 		 number;/*!< Rand number for master election */
};
  
struct punch_msg {
	char		 tag[6];	/*!< TAG identifying the payload */
	int	         punchid;       /*!< Numeric ID of transaction */
	int		 epoch;	        /*!< Timestamp */
	int	         count;          /*!< Numeric ID of transaction */
};

struct transaction {
        int         punchid;
        int         origin;
        int         master;
        int         status;
        int         timestamp;
        int         port_peer;
        int         asymetric;
        int         retry;
        char       *ip_peer;
};

struct transaction *transac_table[65535];

/* uhp_data.c */
int 	port_sanitization(char *);

/* uhp_net.c */
evutil_socket_t		 new_receiver_socket(const char *);
struct sockaddr_in 	*get_sockaddr_in(const char *, const char *);
unsigned char		*get_addr(const char *, const int);
void 			 print_addr(const unsigned char *, const int);

/* uhp_protocol.c */

/**
 * \fun next_operation
 * \brief defines the next sequence in the protocol  
 * If this function is called by the sender callback punch_msg will be null.
 */

void    next_operation(struct transaction **, struct punch_msg *, int);

#endif /* UHP_H */


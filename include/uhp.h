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

#include <limits.h>
#include <event2/event.h>
#include <openssl/rand.h>
#include <stdint.h>
#include <jansson.h>
#include <string.h>
#include <time.h>

#include "error.h"
#include "punch.h"
#include "queue.h"

#define RANGE	        5
#define MAX_PORT        65536
#define	HELLO           0
#define	ACK             1
#define	BYE             2
#define	CANCEL          3
#define	HELLO_TAG       "HELLO"
#define	ACK_TAG         "ACK"
#define	BYE_TAG         "BYE"
#define	CANCEL_TAG      "CANCEL"
#define MAX_BYTES       30 

enum socket_flag{
	SERVER,
	CLIENT
};

enum status {
        PENDING,
        COMPLETE
};

enum operations {
        INIT_TABLE,
        NEXT_MESSAGE,
        UPDATE_TABLE_WITH_MESSAGE,
        MARK_DIRTY,
        MARK_RETRANSMIT,
        END_OF_OPERATIONS
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
	int             punchid;       /*!< Numeric ID of transaction */
	int		tag;	/*!< TAG identifying the payload */
	int		epoch;	        /*!< Timestamp */
	int	        count;          /*!< Numeric ID of transaction */
};

struct transaction {
        int             punchid;
        int             type;
        int             status;
        int             timestamp;
        int             retry;
};

/* struct transaction *transac_table[MAX_PORT]; */

/* uhp_data.c */
int 	                 port_sanitization(char *);
int                      rand2int(uint8_t *, int);
char                    *msg2json(const struct punch_msg *);
struct punch_msg        *json2msg(const char *);

/* uhp_loop.c */
struct transaction      *transac_table[MAX_PORT];

/* uhp_net.c */
evutil_socket_t		 new_receiver_socket(const char *);
struct sockaddr_in 	*get_sockaddr_in(const char *, const char *);
unsigned char		*get_addr(const char *, const int);
void 			 print_addr(const unsigned char *, const int);

/* uhp_protocol.c */

struct punch_msg   *new_punch_msg();
struct punch_msg   *next_msg(struct transaction **, int);
int                 next_operation(struct transaction **,
                                   struct punch_msg *, int);
void                init_table(struct transaction **, int);
void                cleanup_table(struct transaction **);
void                del_punch_msg(struct punch_msg *);
void                new_transaction(struct transaction **, int);
void                del_transaction(struct transaction *);
void                update_transaction(struct transaction **, int, 
                                       struct punch_msg *, int);
#endif /* UHP_H */


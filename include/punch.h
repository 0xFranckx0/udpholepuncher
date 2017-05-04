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


#ifndef PUNCH_H
#define PUNCH_H

#include <stdint.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <jansson.h>
#include <event2/event.h>
#include <event2/listener.h>

/*
Defines a callback that returns the structure info
modify punch function to accept an event base and the callback
*/

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
	void 		*data;
};

struct input_p {
	char 			*address;
	char 			*port;
	char 			*msg;
	struct event_base 	*base; 
};

struct output_p {
	int (*uhp_cb)(int, struct uhp_info *);
	void *metadata;
};

void	punch(struct input_p *, struct output_p *);

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
};
/*
struct list_elem {
        void            *data;
        struct elem     *next;
};

struct list {
	int 			size;
	int             	(*match) (const void *k1, const void *k2);
	void            	(*destroy) (void *data);
	struct list_elem 	*head;
	struct list_elem 	*tail;
};

void list_init(struct list *, void (*destroy) (void *));
void list_destroy(struct list *);
int  list_append_next(struct list *, struct list_elem *, const void *);
int  list_delete_next(struct list *, struct list_elem *, void **);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, elem) ((elem) == (list)->head ? 1 : 0)
#define list_is_tail(list, elem) ((elem)->next == NULL ? 1 : 0)
#define list_data(elem) ((elem)->data)
#define list_next(elem) ((elem)->elem)
*/

#endif /* PUNCH_H  */

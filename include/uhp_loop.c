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
#include <arpa/inet.h>
#include <event.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "uhp.h"
#include "queue.h"

#define MAX_BUF		64000
#define WRITABLE	3
#define UNWRITABLE	0



static struct ev_data {
	struct event_base 	*base;
        struct sockaddr_in      *sin;
	struct uhp_socks 	*s;
	struct uhp_infos 	*infos;
	void			*data;
	void (*uhp_cb)(int flag, struct uhp_info *ui);
};

static void receiver_cb(evutil_socket_t, short, void*);
static void sender_cb(evutil_socket_t, short, void*);

static struct uhp_socks *usock;
static char 		*message;
struct event 		*evs;
struct event 		*evr;

void
sender_cb(evutil_socket_t listener, short event, void *arg)
{
	struct event_base 	*base = arg;
	struct sockaddr_in 	*sin;
	struct timeval 		 time = {2,0};
	int 			 slen = sizeof(sin);
	int 			 len;
	int			 s;
	ssize_t 		 lensnd;

	len = strlen(message) + 1;
	sin = (struct sockaddr_in *)arg;

	if (lensnd = (sendto((int)listener, message, len , 0, 
		(struct sockaddr *) sin, sizeof(*sin))) < 0 ) {
		perror("sendto()");
		event_loopbreak();
		printf("DELETING event\n");
		free(usock->dst);
		free(usock->rport);
		free(usock);
		free(sin);
		event_free(evs);
		exit(-1);
	}

	printf("sent: %s\n",message);
	if (strncmp(message,"stop",4) ==0 ){
		printf("DELETING event\n");
		free(usock->dst);
		free(usock->rport);
		free(usock);
		event_free(evs);
	}
}

void
receiver_cb(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = arg;
	struct sockaddr_in sin;
	ssize_t lenrcv;
	socklen_t slen = sizeof(sin);
	char buf[MAX_BUF];

	memset(buf,0,MAX_BUF);

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		(struct sockaddr *) &sin, &slen)) == -1) {
		perror("recvfrom()");
	}
	printf("SERVER RECEIVED : %s\n", buf);
}

void
punch(struct input_p *ip, struct output_p *op) 
{
        struct ev_data          *arg;
	struct uhp_socks 	*s;
	struct uhp_infos 	*infos;
	struct timeval 		 time = {2,0};
	struct sockaddr_in 	*sin;

	printf("RUN THE PUNCH: %s\n", ip->msg);
	message = ip->msg;

        init_table(transac_table, MAX_PORT);
        
        arg = malloc(sizeof(*arg));
	if (arg == NULL){
		syserr(__func__, "malloc failed");
		exit(-1);
	}
        memset(arg, 0, sizeof(arg));

	arg->s = malloc(sizeof(*arg->s));
	if (arg->s == NULL){
		syserr(__func__, "malloc failed");
		exit(-1);
	}

	s->dst = strndup(ip->address, strlen(ip->address) + 1);
	if (s->dst == NULL){
		syserr(__func__, "strdup");
		free(s);
		exit(-1);
	}

	s->rport = strndup(ip->port, strlen(ip->port) + 1);
	if (s->rport == NULL){
		syserr(__func__, "strdup");
		free(s->dst);
		free(s);
		exit(-1);
	}

	s->r = new_receiver_socket(ip->port);
	if (s->r < 0){
		funerr(__func__, "new_receiver_scoket failed");	
		free(s->dst);
		free(s->rport);
		free(s);
		exit(-1);
	}
	usock = s;

	infos = malloc(sizeof(infos));
	if (infos == NULL){
		syserr(__func__, "malloc");
		free(s->dst);
		free(s->rport);
		free(s);
		exit(-1);
	}

	sin = get_sockaddr_in((const char *)usock->dst, 
				(const char *)usock->rport);

	evs = event_new( ip->base, usock->r, EV_TIMEOUT|EV_PERSIST,
					sender_cb, (void*)sin);
	evr = event_new( ip->base, usock->r, EV_READ|EV_PERSIST,
					receiver_cb, (void*)ip->base);
	event_add(evs, &time);
	event_add(evr, NULL);

}

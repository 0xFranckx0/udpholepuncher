/*
 *  This source code is under development
 *  IN PROGRESS!!!
 */

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
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

evutil_socket_t new_socket(const char *, const char *, int);
static void echo_cb(evutil_socket_t, short, void*);
static void receiver_cb(evutil_socket_t, short, void*);
static void sender_cb(evutil_socket_t, short, void*);

static int 	writer = WRITABLE;
static struct 	uhp_socks *usock;
static char 	*message;

void
sender_cb(evutil_socket_t listener, short event, void *arg)
{
	struct event_base 	*base = arg;
	ssize_t 		 lenrcv;
	ssize_t 		 lensnd;
	char 			*buf = "HELLO from client";
	char 			 rcv[512];
	struct sockaddr_in 	 sin;
	int 			 slen = sizeof(sin);
	int 			 len;
	unsigned char		*addr;

	len = strlen(message) + 1;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(usock->rport));
	inet_pton(AF_INET, usock->dst, &sin.sin_addr);

	if (lensnd = (sendto((int)listener, message, len , 0, 
		(struct sockaddr *) &sin, sizeof(sin))) == -1 ) {
		perror("sendto()");
		event_loopbreak();
	}
	printf("sent: %s\n",message);
}

void
receiver_cb(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = arg;
	struct sockaddr_in sin;
	ssize_t lenrcv, lensnd;
	socklen_t slen = sizeof(sin);
	char buf[MAX_BUF];
	char *msg = "ACK from server";

	memset(buf,0,MAX_BUF);

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		(struct sockaddr *) &sin, &slen)) == -1) {
		perror("recvfrom()");
		event_loopbreak();
	}

	fprintf(stdout,"SERVER RECEIVED : %s\n", buf);
}

int run_udp(struct uhp_socks *s, const char *msg)
{
	struct event_base *base;
	struct event *ev1, *ev2;
	struct timeval time;
	time.tv_sec = 2;
	time.tv_usec = 0;
	usock = s;
	message = msg;
	base = event_base_new();
	if (!base) {
		puts("Couldn't open event base");
		return 1;
	}

	ev1 = event_new( base, usock->r, EV_PERSIST,
					sender_cb, (void*)base);
	ev2 = event_new( base, usock->r, EV_READ|EV_PERSIST,
					receiver_cb, (void*)base);
	event_add(ev1, &time);
	event_add(ev2, NULL);
	event_base_dispatch(base);

	return 0;
}

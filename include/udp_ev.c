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

#include "queue.h"
#include "uhp.h"


evutil_socket_t new_socket(const char *, const char *, int);
static void client_cb(evutil_socket_t, short, void*);
static void server_cb(evutil_socket_t, short, void*);

void
client_cb(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = arg;
	ssize_t lenrcv, lensnd;
	char buf[512];

	memset(buf,0,strlen(buf));

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		NULL,0)) == -1) {
		perror("sendto()");
		event_loopbreak();
	}

	fprintf(stdout,"SENT : %s\n", buf);

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		NULL, NULL)) == -1) {
		perror("recvfrom()");
		event_loopbreak();
	}
}

void
server_cb(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = arg;
	struct sockaddr_in sin;
	ssize_t lenrcv, lensnd;
	socklen_t slen = sizeof(sin);
	char buf[512];

	memset(buf,0,strlen(buf));

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		(struct sockaddr *) &sin, &slen)) == -1) {
		perror("recvfrom()");
		event_loopbreak();
	}

	fprintf(stdout,"RECEIVED : %s\n", buf);
	if (lensnd = (sendto((int)listener, buf,sizeof(lenrcv) , 0, 
		(struct sockaddr *) &sin, slen)) == -1 ) {
		perror("sendto()");
		event_loopbreak();
	}
}

evutil_socket_t
new_socket(const char *addr, const char *port, int type)
{
	evutil_socket_t listener;
    	struct addrinfo *res, hints;


	int optval = 1;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family 	= AF_INET;
	hints.ai_socktype 	= SOCK_DGRAM;
	hints.ai_protocol 	= IPPROTO_UDP;
	hints.ai_addrlen 	= 0;
	hints.ai_addr 		= NULL;
	hints.ai_canonname 	= NULL;
	hints.ai_next 		= NULL;

	switch(type){
	case SERVER:
        	hints.ai_flags = AI_PASSIVE;
		if (getaddrinfo(NULL, addr, &hints, &res) == 1){
			perror("getaddrinfo failed");
			listener = -1;
			goto cleanup;
		}
		if (listener = socket(res->ai_family, res->ai_socktype, 
				res->ai_protocol) < 0){
			perror("socket failed");
			listener = -1;
			goto cleanup;
		}
		if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, 
				&optval, sizeof(optval)) < 0){
			perror("setsockopt failed");
			listener = -1;
			goto cleanup;
		}
		evutil_make_socket_nonblocking(listener);
		if (bind(listener, res->ai_addr, res->ai_addrlen) < 0){
			perror("bind failed");
			listener = -1;
			goto cleanup;
		}
		break;
	case CLIENT:
        	hints.ai_flags = 0;
		if (getaddrinfo(addr, port, &hints, &res) == 1){
			perror("getaddrinfo failed");
			listener = -1;
			goto cleanup;
		}
		if (listener = socket(res->ai_family, res->ai_socktype, 
				res->ai_protocol) <0){
			perror("socket failed");
			listener = -1;
			goto cleanup;
		}
		evutil_make_socket_nonblocking(listener);
		if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, 
				&optval, sizeof(optval)) < 0){
			perror("setsockopt failed");
			listener = -1;
			goto cleanup;
		}
		if (connect(listener,res->ai_addr, res->ai_addrlen) == 0){
			perror("connect failed");
			listener = -1;
			goto cleanup;
		}
		break;
	}

cleanup:
	if (res != NULL)
		freeaddrinfo(res);	

	return listener;
}

evutil_socket_t	
new_client_socket(const char *addr, const char *port)
{
	return new_socket(addr, port, CLIENT);
}

evutil_socket_t	
new_server_socket(const char *port)
{
	return new_socket(NULL, port, SERVER);
}

int run_udp(evutil_socket_t fd1, evutil_socket_t fd2)
{
	struct event_base *base;
	struct event *ev1, *ev2;

	base = event_base_new();
	if (!base) {
		puts("Couldn't open event base");
		return 1;
	}

	ev1 = event_new( base, fd1, EV_READ|EV_PERSIST,
					client_cb, (void*)base);
	ev2 = event_new( base, fd2, EV_READ|EV_PERSIST,
					server_cb, (void*)base);
	event_add(ev1, NULL);
	event_add(ev2, NULL);
	event_base_dispatch(base);

	return 0;
}

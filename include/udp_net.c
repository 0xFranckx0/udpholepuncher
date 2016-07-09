#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "uhp.h"

#define MAX_BUF		64000
#define WRITABLE	3
#define UNWRITABLE	0


unsigned char*
get_addr( const char *addr, const int domain)
{
	unsigned char	*buf;
	int		 s;

	buf = malloc(sizeof (struct in6_addr));
	if (buf == NULL){
		perror("malloc");
		goto error;
	}

	s = inet_pton (domain, addr, buf);
	if (s <= 0){
		if (s == 0)
      			fprintf (stderr, "Not in presentation format");
    		else
      			perror ("inet_pton");
		goto error;
	}

	return buf;
error:
	if (buf)
		free(buf);
	return NULL;
}

void
print_addr(const unsigned char *addr, const int domain)
{
	char 		 str[INET6_ADDRSTRLEN];

	if (inet_ntop(domain, addr, str, INET6_ADDRSTRLEN) == NULL) {
		perror("inet_ntop");
	}

	printf("%s\n", str);
}

evutil_socket_t
new_socket(const char *addr, const char *port, int type)
{
	evutil_socket_t listener;
    	struct addrinfo *res, hints;
	int rv, s;

	int optval = 1;
	memset(&hints, 0, sizeof(struct addrinfo));
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
		if ((rv = getaddrinfo(NULL, port, &hints, &res)) != 0){
			perror("getaddrinfo failed");
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			listener = -1;
			goto cleanup;
		}
		if ( (listener = socket(res->ai_family, res->ai_socktype, 
				res->ai_protocol)) < 0){
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
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			listener = -1;
			goto cleanup;
		}
		if ((listener = socket(res->ai_family, res->ai_socktype, 
				res->ai_protocol)) < 0){
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
		if (connect(listener,res->ai_addr, res->ai_addrlen) == -1){
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
new_sender_socket(const char *addr, const char *port)
{
	return new_socket(addr, port, CLIENT);
}

evutil_socket_t	
new_receiver_socket(const char *port)
{
	return new_socket(NULL, port, SERVER);
}

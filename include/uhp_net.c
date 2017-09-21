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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>

#include "uhp.h"

#define MAX_BUF		64000
#define WRITABLE	3
#define UNWRITABLE	0


static evutil_socket_t		 new_socket(const char*, const char*);

evutil_socket_t
new_socket(const char *addr, const char *port)
{
	evutil_socket_t listener;
    	struct addrinfo *res, hints;
	int rv, s;

	int optval;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family 	= AF_INET;
	hints.ai_socktype 	= SOCK_DGRAM;
	hints.ai_protocol 	= IPPROTO_UDP;
	hints.ai_addrlen 	= 0;
	hints.ai_addr 		= NULL;
	hints.ai_canonname 	= NULL;
	hints.ai_next 		= NULL;
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
        optval = 1;
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

cleanup:
	if (res != NULL)
		freeaddrinfo(res);	

	return listener;
}

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
new_receiver_socket(const char *port)
{
	return new_socket(NULL, port);
}


struct sockaddr_in *
get_sockaddr_in(const char * dst, int port)
{
	struct sockaddr_in 	*sin;
        char *buf;
	int s;

	errno = 0; 


	sin = malloc(sizeof(*sin));
	if (sin == NULL){
		syserr(__func__, "malloc");
		exit(-1);
	}
	sin->sin_family = AF_INET;
	//sin->sin_port = htons(atoi(port));
	sin->sin_port = htons(port);

	s = inet_pton(AF_INET, dst, &sin->sin_addr);
	if (s <= 0){
		if (s == 0) {
      			perror ("Invalid IPv4 address");
			exit(-1);
		}
    		else {
      			perror ("System error");
			exit(-1);
		}	
	}

	return sin;

not_a_number:
	perror("not a number");
	return NULL;

out_of_range:
	perror("out_of_range");
	return NULL;

}

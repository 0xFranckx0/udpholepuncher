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

#define LOG_PATH  "/dev/log"

void
ux_cb(evutil_socket_t listener, short event, void *arg)
{
        struct event_base *base = arg;
        struct sockaddr_in sin;
        ssize_t lenrcv, lensnd;
        socklen_t slen = sizeof(sin);
        char buf[512];

        memset(buf,0,strlen(buf));
        /* Recv the data, store the address of the sender in server_sin */
    
        if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
                (struct sockaddr *) &sin, &slen)) == -1) {
            perror("recvfrom()");
            event_loopbreak();
        }
        
        fprintf(stdout,"RECEIVED : %s\n", buf);
}

int run_log()
{
        evutil_socket_t listener;
        struct sockaddr_un sin;
        struct event_base *base;
        struct event *listener_event;

        base = event_base_new();
        if (!base) {
            puts("Couldn't open event base");
            return 1;
        }

        memset(&sin, 0, sizeof(sin));
        sin.sun_family = AF_UNIX;
        strcpy(sin.sun_path, LOG_PATH);
        
        listener = socket(AF_UNIX,SOCK_DGRAM,0);
	if(listener < 0){
		perror("");
		exit(0);
	}
        evutil_make_socket_nonblocking(listener);
        
        int optval = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

        if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0){
                perror("bind()");
                exit(EXIT_FAILURE);
        }
        listener_event = event_new( base, listener, EV_READ|EV_PERSIST,
                                    ux_cb, (void*)base);
        event_add(listener_event, NULL);
        event_base_dispatch(base);

        return 0;
}


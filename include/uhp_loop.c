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

#define MAX_BUF		64000
#define WRITABLE	3
#define UNWRITABLE	0


static void sender_cb(evutil_socket_t, short, void*);
static void receiver_cb(evutil_socket_t, short, void*);

static struct event_base *stop_base;
static struct uhp_carrier *data_out;

int max_hints = 5;

void
sender_cb(evutil_socket_t listener, short event, void *arg)
{
        struct uhp_sock *data = arg;
	ssize_t 		 lensnd;
        char *msg = "NUMERO 2";
	int len = strlen(msg) + 1;

        
	if (lensnd = (sendto((int)listener, (const void *)msg, len , 0, 
		        (struct sockaddr *) data->sin, 
                        sizeof(*data->sin))) < 0 ) {

	        perror("sendto()");
		event_base_loopbreak(stop_base);
        }

        if (data->max_hints > 0){
                data->max_hints--;
                printf("MAX HINTS: %d\n", data->max_hints);
        } else {
                data_out->data_punch = dup_sock(data);
                data->selected = 1;
		event_base_loopbreak(stop_base);
        }
}

void
receiver_cb(evutil_socket_t listener, short event, void *arg)
{
        struct uhp_sock *data = arg;
        struct sockaddr sin;
	ssize_t lenrcv;
	socklen_t slen = sizeof(sin);
	char buf[MAX_BUF];

	memset(buf,0,MAX_BUF);

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		&sin, &slen)) == -1) {
		perror("recvfrom()");
		event_base_loopbreak(stop_base);
	}
	printf("SERVER RECEIVED : %s\n", buf);
/*
        data->selected = 1;
        data_out->data_punch = NULL;
	event_base_loopbreak(stop_base);
*/        
}

void
punch_start(struct uhp_carrier *in, struct event_base *base) 
{
        struct event 		*evs, *evr;
	struct timeval 		 time = {2,0};
        struct uhp_sock          *data = NULL;
        data_out =               in;

        stop_base = base;

        init_table(transac_table, MAX_PORT);
        
        for (int i = 0; slist_is_empty(in->items) > 0; i++){
                if ((data = (struct uhp_sock *)slist_pop(in->items)) != NULL) {
                        evs = event_new(base, data->sock, 
                               EV_TIMEOUT|EV_PERSIST, sender_cb, (void *)data);
                        in->list_evts[0][i] = evs;

                        evr = event_new(base, data->sock,    
                               EV_READ|EV_PERSIST, receiver_cb, (void *)data);
                        in->list_evts[1][i] = evr;

                        event_add(evs, &time);
                        event_add(evr, NULL);
                } else {
                        printf("NO DATA\n");
                        break;
                }
        }
}

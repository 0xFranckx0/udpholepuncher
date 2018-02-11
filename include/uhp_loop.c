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
static struct output_p *data_out;

int max_hints = 5;

void
sender_cb(evutil_socket_t listener, short event, void *arg)
{
        struct input_p *data = arg;
	ssize_t 		 lensnd;
        char *msg = data->get_message(data);
	int len = strlen(msg) + 1;

        
	if (lensnd = (sendto((int)listener, (const void *)msg, len , 0, 
		        (struct sockaddr *) data->sin, 
                        sizeof(*data->sin))) < 0 ) {

	        perror("sendto()");
		//event_base_loopbreak(stop_base);
        }

        printf("RECEIVER Port: %s MESSAGE: %s\n", data->port, msg);


        if (data->max_hints > 0){
                data->max_hints--;
                printf("MAX HINTS: %d\n", data->max_hints);
        } else {
                data_out->data_punch = dup_input(data);
                data->selected = 1;
		event_base_loopbreak(stop_base);
        }
}

void
receiver_cb(evutil_socket_t listener, short event, void *arg)
{
        struct input_p *data = arg;
	ssize_t lenrcv;
	socklen_t slen = sizeof(data->sin);
	char buf[MAX_BUF];

	memset(buf,0,MAX_BUF);

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		(struct sockaddr *) &data->sin, &slen)) == -1) {
		perror("recvfrom()");
		event_base_loopbreak(stop_base);
	}
	printf("SERVER RECEIVED : %s\n", buf);

        data->selected = 1;
        data_out->data_punch = NULL;
	event_base_loopbreak(stop_base);
}

void
punch_start(struct uhp_input *in, struct event_base *base) 
{
        struct event 		*evs, *evr;
	struct timeval 		 time = {2,0};
        struct input_p          *data = NULL;
        data_out =               in->out;

        stop_base = base;

        init_table(transac_table, MAX_PORT);
        
        for (int i = 0; slist_is_empty(in->items) > 0; i++){
                if ((data = (struct input_p *)slist_pop(in->items)) != NULL) {
                        evs = event_new(base, data->sock, 
                               EV_TIMEOUT|EV_PERSIST, sender_cb, (void *)data);
                        in->out->list_evts[0][i] = evs;

                        evr = event_new(base, data->sock,    
                               EV_READ|EV_PERSIST, receiver_cb, (void *)data);
                        in->out->list_evts[1][i] = evr;

                        event_add(evs, &time);
                        event_add(evr, NULL);
                } else {
                        printf("NO DATA\n");
                        break;
                }
        }
}

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
char *MSG = "TEST";

void
sender_cb(evutil_socket_t listener, short event, void *arg)
{
        struct uhp_data *data = arg;
	ssize_t 		 lensnd;
        char *msg = data->in->get_message(data->in);
	int len = strlen(msg) + 1;

        
	if (lensnd = (sendto((int)listener, (const void *)msg, len , 0, 
		        (struct sockaddr *) data->in->sin, 
                        sizeof(*data->in->sin))) < 0 ) {

	        perror("sendto()");
		event_base_loopbreak(stop_base);
        }

        printf("RECEIVER Port: %s MESSAGE: %s\n", data->in->port, msg);

	if (strncmp(msg,data->in->port,len) == 0 ){
		printf("DELETING event\n");
		event_base_loopbreak(stop_base);
	}
}

void
receiver_cb(evutil_socket_t listener, short event, void *arg)
{
        struct input_p *in = arg;
	ssize_t lenrcv;
	socklen_t slen = sizeof(in->sin);
	char buf[MAX_BUF];

	memset(buf,0,MAX_BUF);

	if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
		(struct sockaddr *) &in->sin, &slen)) == -1) {
		perror("recvfrom()");
		event_base_loopbreak(stop_base);
	}
	printf("SERVER RECEIVED : %s\n", buf);
}


void
punch_start(struct slist *list, struct event_base *base) 
{
        struct event 		*evs, *evr;
	struct timeval 		 time = {2,0};
        struct uhp_data         *data = NULL;
        /* int i; */
        stop_base = base;
        printf("%s\n",MSG);

        init_table(transac_table, MAX_PORT);
        
        /* for (i = 0; slist_is_empty > 0; i++){ */
        while (slist_is_empty > 0){
                if ((data = (struct uhp_data *)slist_pop(list)) != NULL) {
                        evs = event_new(base, data->in->sock, 
                               EV_TIMEOUT|EV_PERSIST, sender_cb, (void *)data);
                        evr = event_new(base, data->in->sock,    
                               EV_READ|EV_PERSIST, receiver_cb, (void *)data);
                        event_add(evs, &time);
                        event_add(evr, NULL);
                } else {
                        printf("NO DATA\n");
                        break;
                }
        }
}

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

void
readcb(struct bufferevent *bev, void *ctx)
{
}

void
errorcb(struct bufferevent *bev, short error, void *ctx)
{
}

void
udp_cb(evutil_socket_t listener, short event, void *arg)
{
    struct event_base *base = arg;
    struct sockaddr_in server_sin;
    ssize_t lenrcv, lensnd;
    socklen_t server_sz = sizeof(server_sin);
    char buf[512];

    memset(buf,0,strlen(buf));
    /* Recv the data, store the address of the sender in server_sin */
    
    if (lenrcv = (recvfrom((int)listener, &buf, sizeof(buf) - 1, 0,
        (struct sockaddr *) &server_sin, &server_sz)) == -1) {
        perror("recvfrom()");
        event_loopbreak();
    }
    fprintf(stdout,"RECEIVED : %s\n", buf);
    /* Send the data back to the client */
    if (lensnd = (sendto((int)listener, buf,sizeof(lenrcv) , 0, 
        (struct sockaddr *) &server_sin, server_sz)) == -1 ) {
       perror("sendto()");
       event_loopbreak();
    }
}

int run_udp()
{
        evutil_socket_t listener;
        struct sockaddr_in sin;
        struct event_base *base;
        struct event *listener_event;

        base = event_base_new();
        if (!base) {
            puts("Couldn't open event base");
            return 1;
        }

        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = 0;
        sin.sin_port = htons(4000);
        
        listener = socket(AF_INET,SOCK_DGRAM,0);
        evutil_make_socket_nonblocking(listener);
        
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

        if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0){
                perror("bind()");
                exit(EXIT_FAILURE);
        }
        listener_event = event_new( base, listener, EV_READ|EV_PERSIST,
                                    udp_cb, (void*)base);
        event_add(listener_event, NULL);
        event_base_dispatch(base);

        return 0;
}


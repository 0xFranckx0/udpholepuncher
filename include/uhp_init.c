#include <stdlib.h>

#include "punch.h"
#include "uhp.h"


struct slist *
punch_init(char **pt, int sz, char *addr)
{
        struct l_ports *ports = NULL;
        struct slist *l_data   = NULL;
        struct input_p *in = NULL; 
        struct output_p *out = NULL; 
        struct uhp_data d; 
        int i;

        ports = parse_ports(pt, sz);
        if (ports == NULL){
                perror("ports error");
                goto error;
        }
                
        l_data = malloc(sizeof(struct slist));
        if (l_data == NULL) {
                perror("Malloc Failed");
                goto error;
        }
        slist_init(l_data, sizeof(struct uhp_data));

        for (i = 0; i < ports->size; i++) {
                in = malloc(sizeof(struct input_p));
                if (in == NULL) {
                        perror("Malloc Failed");
                        goto error;
                }
                out = malloc(sizeof(struct output_p));
                d.in = in;
                d.out = out;
	        in->address = strdup(addr);	
                in->base = NULL;
                /*
		in->base = event_base_new();
		if (in->base == NULL) {
			perror("Couldn't open event base");
			goto error;
		}
                */
		in->port_int = ports->p[i];
                in->port = ports->p_str[i];
                in->sock = new_receiver_socket(in->port);
                if (in->sock < 0){
                        perror("Failed to create socket");
                        free(in->base);
                        continue;
                }
	        in->sin = get_sockaddr_in((const char *)in->address, 
				in->port_int);
		in->msg = strdup("HELLO");
		if (in->msg == NULL){
			perror("strdup failed");
			goto error;
		}
        
                slist_insert(l_data, &d);
        }
        

        free(ports);
        return l_data;

error:
        if (l_data != NULL)
                free(l_data);
        if (ports != NULL)
                free(ports);
        
        return NULL;
}

void
input_free(struct input_p *in)
{
        if (in != NULL){
                close(in->sock);
                if (in->sin)
                        free(in->sin);
                if (in->base)
                        event_base_free(in->base);
                if (in->address)
                        free(in->address);
                if (in->port)
                        free(in->port);
                if (in->msg)
                        free(in->msg);
                free(in);
        }

}


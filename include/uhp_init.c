#include <stdlib.h>

#include "punch.h"
#include "uhp.h"


struct slist *
punch_init(char **pt, int sz, char *addr)
{
        struct l_ports *ports = NULL;
        struct slist *l   = NULL;
        struct input_p *in = NULL; 
        struct output_p *out; 
        struct uhp_data d =  {
                in,
                out
        };
        int i;


        ports = parse_ports(pt, sz);
        if(ports == NULL){
                perror("ports error");
                goto error;
        }
                
        in = malloc(sizeof(struct input_p));
        if (in == NULL) {
                perror("Malloc Failed");
                goto error;
        }

        l = malloc(sizeof(struct slist));
        if (l == NULL) {
                perror("Malloc Failed");
                goto error;
        }
        slist_init(l, sizeof(struct uhp_data));

	in->address = strdup(addr);	

        for (i = 0; i < sz; i++) {
		in->base = event_base_new();
		if (in->base == NULL) {
			perror("Couldn't open event base");
			goto error;
		}
		in->port_int = ports->p[i];
                in->sock = new_receiver_socket(in->port);
                if (in->sock < 0){
                        perror("Failed to create socket");
                        free(in->base);
                        continue;
                }
	        in->sin = get_sockaddr_in((const char *)in->address, 
				(const char *)in->port);
		in->port = ports->p_str[i];
		in->msg = strdup("HELLO");
		if (in->msg == NULL){
			perror("strdup failed");
			goto error;
		}
        
                slist_insert(l, &d);
        }

        return l;

error:
        if (l != NULL)
                free(l);
        if (ports != NULL)
                free(ports);
        
        return NULL;
}

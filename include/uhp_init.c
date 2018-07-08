#include <stdlib.h>

#include "punch.h"
#include "uhp.h"


struct slist *
punch_init(char **pt, int sz, char *addr)
{
        struct l_ports *ports = NULL;
        struct slist *l_data   = NULL;
        struct uhp_sock *in = NULL; 
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

        slist_init(l_data, sizeof(struct uhp_sock));

        for (i = 0; i < ports->size; i++) {
                in = malloc(sizeof(struct uhp_sock));
                if (in == NULL) {
                        perror("Malloc Failed");
                        goto error;
                }
		in->port_int = ports->p[i];
                in->port = ports->p_str[i];
                in->sock = new_receiver_socket(in->port);
                if (in->sock < 0){
                        perror("Failed to create socket");
                        continue;
                }
                in->selected = 0;
                in->max_hints = 4;
		in->dst = strdup(addr);
		
	        if ((in->sin = get_sockaddr_in((const char *)addr, 
				in->port_int)) == NULL ) 
			goto error;

        
                slist_insert(l_data, in);
        }

	free(ports->p_str);
	free(ports->p);
        free(ports);

        return l_data;

error:
        if (l_data != NULL)
                free(l_data);
        if (ports->p_str != NULL)
		free(ports->p_str);
        if (ports->p != NULL)
		free(ports->p);
        if (ports != NULL)
		free(ports);
        
        return NULL;
}

void
sock_free(struct uhp_sock *in)
{
        if (in != NULL){
                if (in->selected < 1)
                        close(in->sock);
                if (in->sin)
                        free(in->sin);
                if (in->port)
                        free(in->port);
		if (in->dst)
			free(in->dst);
                free(in);
        }

}


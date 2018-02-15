#ifndef PUNCH_H
#define PUNCH_H

struct slist;
/* uhp_sock is passed to punch loop to create events */
struct uhp_sock {
        int                      sock;
	int			 port_int;
        int                      max_hints;
        int                      selected;
	char 			*address;
	char 			*msg;
	char 			*port;
        struct sockaddr_in      *sin;
};

struct uhp_carrier {
        struct slist *items;    /* list of uhp_socks */
        struct event **list_evts[2];
        struct uhp_sock *data_punch;        
	void    *metadata;
};

struct l_ports {
        int   size;
        int  *p;
        char **p_str;
};

/* uhp_data.c */
struct l_ports *parse_ports(char **, int);

/* uhp_loop.c */
void	punch_start(struct uhp_carrier *, struct event_base *);

/* uhp_init.c */
struct slist *punch_init(char **, int, char *); 
void          sock_free(struct uhp_sock *);

#endif /* PUNCH_H  */

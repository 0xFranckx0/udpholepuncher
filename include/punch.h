#ifndef PUNCH_H
#define PUNCH_H

#define SELF 0
#define PEER 1


/**
 * \struct uhp_info
 * \brief uhp_info is the struct returned by libuhp to the caller program once
 *	  a NAT was punched and provides informations about socket, master role
 *	  and the port to reach.
 *
 */
struct uhp_info {
	int 	 	 sock;	/*!< Socket on which communication is enabled */
	int  	         master;/*!< Defines a master: SELF or PEER */
	void 		*data;
	char 		*port;	
	char 		*dst;	/*!< Destination address */
};

/* input_p is passed to punch loop to create events */
struct input_p {
        char * (*get_message)(struct input_p *);
	struct event_base 	*base; 
        struct sockaddr_in      *sin;
	char 			*address;
	char 			*msg;
	char 			*port;
        int                      sock;
	int			 port_int;
};

struct output_p {
        int sock_punch;        
	int (*uhp_cb)(int, struct uhp_info *);
	void    *metadata;
};

struct uhp_input {
        struct slist *items;
        struct output_p *out;
};

struct uhp_data {
        struct input_p  *in;
        struct output_p *out;
};

struct l_ports {
        int   size;
        int  *p;
        char **p_str;
};
/* uhp_data.c */
struct l_ports *parse_ports(char **, int);
char * simple_message(struct input_p *); 

/* uhp_loop.c */
struct slist;
void	punch_start(struct uhp_input *, struct event_base *);

/* uhp_init.c */
struct slist *punch_init(char **, int, char *); 
void          input_free(struct input_p *);
#endif /* PUNCH_H  */

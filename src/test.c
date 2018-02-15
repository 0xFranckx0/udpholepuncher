#include <config.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <include/punch.h>

static int p_cb(int, struct uhp_info *);

int
p_cb(int flag, struct uhp_info *ui)
{
	
	return 0;
}

int
main (int argc, char **argv)
{

	struct event_base 	*base; 
	struct uhp_info 	*ui;
	char 			*port;
	char 			*msg;
	char 			*address;
	int			 c;

	struct uhp_sock 		*ip;
	struct output_p 	*op;

	printf("INITIALIZATION\n");

	ip = malloc(sizeof(*ip));	
	if (ip == NULL){
		perror("malloc");
		exit(-1);
	}

	while ((c = getopt(argc, argv, "a:m:p:")) != -1) {
		switch (c) {
		case 'a':
			printf("Setting a \n");
			address = optarg;
			break;
		case 'p':
			printf("Setting p \n");
			port = optarg;
			break;
		case 'm':
			printf("Setting m \n");
			msg = optarg;
			break;
		default:
			printf("Usage: ");
			printf("test -a 192.168.0.1 -p 54321 -m message\n");
			exit(-1);
		}
	}
	
	ip->address = strdup(address);	
	if (ip->address == NULL){
		perror("strdup failed");
		exit(-1);
	}
	printf("INITIALIZATION: ADDRESS: %s\n",ip->address);
	ip->port = strdup(port);	
	if (ip->port == NULL){
		perror("strdup failed");
		exit(-1);
	}
	printf("INITIALIZATION: PORT: %s\n", ip->port);

	ip->msg = strdup(msg);	
	if (ip->msg == NULL){
		perror("strdup failed");
		exit(-1);
	}
	printf("INITIALIZATION: MSG: %s\n", ip->msg);
	ip->base = event_base_new();
	if (ip->base == NULL) {
		perror("Couldn't open event base");
		exit(-1);
	}

	op = malloc(sizeof(*op));	
	if (op == NULL){
		perror("malloc");
		exit(-1);
	}
	op->uhp_cb = p_cb;
	op->metadata = NULL;


	printf("CALL PUNCH\n");
	punch(ip,op);

	printf("DISPATCH\n");
	event_base_dispatch(ip->base);	

	return 0;

}

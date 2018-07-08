#include <config.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <include/punch.h>

#include <include/uhp.h>

static void usage();
static void test_parse_ports(char **, int);
static void test_punch_init(char **, int, char *);

int
main (int argc, char **argv)
{
	int			 c;
	int			 options = 0;
	char 			*address;
	char 			*port;
	char 			*msg;
	char			*ports[2] = {"33333", "33334-33335"};

	printf("INITIALIZATION\n");

	while ((c = getopt(argc, argv, ":a:m:p:")) != -1) {
		switch (c) {
		case 'a':
			address = optarg;
			options++;
			break;
		case 'p':
			port = optarg;
			options++;
			break;
		case 'm':
			msg = optarg;
			options++;
			break;
		default:
			usage();
			exit(-1);
		}
	}
	/*
	printf("Address: %s\nPort: %s\nMessage: %s\n", address, port, msg);
	*/
	/*
	test_parse_ports(ports,2);
	*/
	test_punch_init(ports,2, address);
		
	return 0;
}

void 
usage(){
	printf("Usage: ");
	printf("test -a 192.168.0.1 -p 54321 -m message\n");
}


void
test_parse_ports(char **ports, int len)
{
	struct	l_ports		*lp;
	lp = parse_ports(ports, 2);
	if (lp == NULL){
		perror("Error while parsing ports");
		return; 
	}

	for (int i = 0; i < lp->size; i++){
		printf("Decimal = %d, string = %s\n", lp->p[i], lp->p_str[i]);
	}
		
	for (int i = 0; i < lp->size; i++){
		if (lp->p_str[i] != NULL)
			free(lp->p_str[i]);
	}
	free(lp->p_str);
	free(lp->p);
	free(lp);
}

void
test_punch_init(char **ports, int len, char *address)
{	
	struct slist *it = NULL;
	if ((it = punch_init(ports, len, address)) 
                        == NULL) {
                perror("Punch init failed");
                return;
        }
	while (slist_is_empty(it) > 0) 
		sock_free(slist_pop(it));

	free(it);	
}

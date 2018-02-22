#include <config.h>
#include <ctype.h>
#include <event.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/rand.h>

#include <include/punch.h>

#include <include/uhp.h>

#define MAX_BUF		64000

static void print_data_int(void *);
static int comp_data_int(void *, void *);
static void delete_data_int(void *);
/*static int p_cb(int, struct uhp_carrier *);*/
static void usage();

int
main (int argc, char **argv)
{
	int			 c;
	int			 options = 0;
	char 			*address;
	char 			*port;
	char 			*msg;

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
	printf("Address: %s\nPort: %s\nMessage: %s", address, port, msg);

	return 0;
}

void 
usage(){
	printf("Usage: ");
	printf("test -a 192.168.0.1 -p 54321 -m message\n");
}


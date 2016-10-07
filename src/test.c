#include <config.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <include/punch.h>

#define SPORT "12345"
#define RPORT "54321"
#define DEST  "192.168.0.173"
static int p_cb(int, struct uhp_info *);

int
p_cb(int flag, struct uhp_info *ui)
{
	
	return 0;
}

int
main (int argc, char **argv)
{
/*
#ifdef UHP_DEBUG_MODE
	char *uhpport =  "4000";
	printf("UHP port: %s\n", uhpport);
#endif*/ /* UHP_DEBUG_MODE */
/*
#ifdef HAVE_DEVRAND
	char *devrand =  "OK";
	printf("dev random: %s\n", devrand);
#endif*/ /* HAVE_DEVRAND */
/*
#ifdef HAVE_DEVURAND
	char *devurand =  "OK";
	printf("dev urandom: %s\n", devurand);
#endif*/ /* HAVE_DEVURAND */

	struct event_base 	*base; 
	struct uhp_info 	*ui;
	char 			*port;
	char 			*msg;
	char 			*address;
	int			 c;

	struct input_p 		 ip = {
		NULL,
		NULL,
		NULL,
		NULL
	};
	struct output_p 	op = {
		p_cb,
		NULL
	};
	while ((c = getopt(argc, argv, "a:m:p:")) != -1) {
		switch (c) {
		case 'a':
			printf("Setting a \n");
			ip.address = optarg;
			break;
		case 'p':
			printf("Setting p \n");
			ip.port = optarg;
			break;
		case 'm':
			printf("Setting m \n");
			ip.msg = optarg;
			break;
		default:
			printf("Usage: ");
			printf("test -a 192.168.0.1 -p 54321 ");
			exit(-1);
		}
	}

	base = event_base_new();
	if (base == NULL) {
		puts("Couldn't open event base");
		return -1;
	}

//	event_base_loopcontinue(base);

	punch(&ip,&op);
	

	return 0;

}

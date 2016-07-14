/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/24/2016 18:150:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Franck Rupin, franck.rupin@gmail.com
 *
 * =====================================================================================
 */

#include <config.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <include/uhp.h>

#define SPORT "12345"
#define RPORT "54321"
#define DEST  "192.168.0.173"

//static struct filter_list      filters;
int
main (int argc, char **argv)
{
#ifdef UHP_DEBUG_MODE
	char *uhpport =  "4000";
	printf("UHP port: %s\n", uhpport);
#endif /* UHP_DEBUG_MODE */

#ifdef HAVE_DEVRAND
	char *devrand =  "OK";
	printf("dev random: %s\n", devrand);
#endif /* HAVE_DEVRAND */

#ifdef HAVE_DEVURAND
	char *devurand =  "OK";
	printf("dev urandom: %s\n", devurand);
#endif /* HAVE_DEViURAND */

evutil_socket_t 	 server;
	//evutil_socket_t client;
	struct uhp_socks 	*s;
	char 			*address;
	char 			*port;
	char 			*msg;
	char 			*message;
	int			 c;

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
			printf("test -a 192.168.0.1 -p 54321 ");
			exit(-1);
		}
	}
	printf("%s:%s---->%s\n",address, port, msg);

	s = malloc(sizeof(s));
	if (s == NULL){
		perror("malloc():");
		exit(1);
	}
	printf("s->rport: %s\n", port);
	s->rport = strdup(port);
	printf("s->dst: %s\n", address);
	s->dst = strdup(address);
//	s->s = new_sender_socket(s->dst,s->rport);
	s->r = new_receiver_socket(s->rport);
	printf("MSG: %s\n", msg);
	message = strdup(msg);
	printf("MESSAGE: %s\n", message);
	run_udp(s,message);
//	free(s->sport);
	free(s->rport);
	free(s->dst);
	free(s);
//        struct hdr_pkt *pkt;

//    puts ("This is :" PACKAGE_STRING ".");
//        pkt = new_keepalive();
//        printf("ID : %d\n",pkt->id);
//        printf("TAG: %s\n",pkt->pl.msg);
//        free_pkt(pkt);
/*    run_log();*/
/*    run_udp(); */
/*    char *str;
    str = malloc(4 * sizeof(char));
    if ( str == NULL) {
        err_sscb(__func__, "malloc");
        err_pb(stderr);
        return -1;
    }
    free( str);

    puts ("This is :" PACKAGE_STRING ".");

    int res;
    res = uhp_new();
    
    if (res == -1) {
        err_sb(__func__, "error code is %d", res);
        err_pb(stderr);
    }
    
    uhp_print();
*/
    return 0;
}

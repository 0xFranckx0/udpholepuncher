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
#include <stdio.h>

#include <include/uhp.h>

//static struct filter_list      filters;
int
main (void)
{

	evutil_socket_t server;
	//evutil_socket_t client;
	struct uhp_socks *s;
	
	s = malloc(sizeof(s));
	if (s == NULL){
		perror("malloc():");
		exit(1);
	}
	s->port = "12345";
	s->dst = "192.168.0.114";

	s->sock = new_client_socket(s->dst,s->port);
	//server = new_server_socket("12344");
	run_udp(s);

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

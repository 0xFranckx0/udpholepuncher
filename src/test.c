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

int
main (void)
{

	evutil_socket_t client, server;
	
	client = new_client_socket("127.0.0.1","12345");
	server = new_server_socket("12345");
	run_udp(client,server);

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

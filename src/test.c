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

#include <lib/uhp.h>

int
main (void)
{
    run_udp();
/*    run_log();*/
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

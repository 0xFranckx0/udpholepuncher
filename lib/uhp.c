/*
 * =====================================================================================
 *
 *       Filename:  uhp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/16 18:56:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Franck Rupin (), franck.rupin@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

#include "uhp.h"

struct hdr_pkt*
new_keepalive()
{
        struct hdr_pkt *keep;
        int len;

        keep = malloc(sizeof(*keep));
        if (keep == NULL){
            err_sscb(__func__, "malloc");
            err_pb(stderr);
            return NULL;
        }
        keep->id = KEEPALIVE;
        len = (int)(strlen(KEEPALIVE_TAG)+1);
        keep->pl.msg = malloc(sizeof(char)*len);
        if (keep->pl.msg == NULL){
            err_sscb(__func__, "malloc");
            err_pb(stderr);
            free(keep);
            return NULL;
        }
        strcpy(keep->pl.msg, KEEPALIVE_TAG);
        
        return keep;
}

void
free_pkt(struct hdr_pkt *pkt)
{
        if(pkt != NULL){
            switch(pkt->id){
                case KEEPALIVE:
                        if(pkt->pl.msg != NULL)
                            free(pkt->pl.msg);
                        free(pkt);
                        break;
                 default:
                        break;
             }
        }
}

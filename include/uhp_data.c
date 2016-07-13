/*
    libuhp is a library dedicated to hole punching NAT traversal over UDP
    Copyright (C) <2016>  <Franck Rupin franck@holepuncher.io>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


    <libuhp>  Copyright (C) <2016>  <Franck Rupin>
    This program comes with ABSOLUTELY NO WARRANTY.
    This is free software, and you are welcome to redistribute it
    under certain conditions.
*/



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
/*
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
*/
void
free_pkt(struct hdr_pkt *pkt)
{
        if(pkt != NULL){
            switch(pkt->id){
                 default:
                 break;
             }
        }
}


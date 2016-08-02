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

#include <stdio.h>

#include "uhp.h"

#include "uhp_utils.h"

#define MAX_BYTES 4

struct base*
new_base(char *port)
{
	struct 		base *b;
	
	b = malloc(sizeof(b));
	if (b == NULL) {
		perror("malloc()");
		goto cleanup;
	}

	b->rand = uhp_rand(MAX_BYTES);
	if (rand == NULL) {
		perror("uhp_rand()");
		goto cleanup;
	}

	b->port = strndup(port, strlen(port) + 1);
	if (b->port == NULL){
		perror("strndup()");
		goto cleanup;
	}
	if ( b->timestamp = (int)time(NULL) < 0 ) {
		perror("time()");
		goto cleanup;
	}

	return b;

cleanup:

	if (b->port != NULL)
		free(b->port);

	if (b->rand != NULL)
		free(b->rand);

	if (b != NULL)
		free(b);

	return NULL;
}

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


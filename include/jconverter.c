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
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#include "uhp.h"

static json_t*
keep2json(void *pkt)
{
	json_t *obj;
	return obj;
}

static json_t*
hello2json(void *pkt)
{
	json_t *obj;
	return obj;
}

static json_t*
ack2json(void *pkt)
{
	json_t *obj;
	return obj;
}

static json_t*
bye2json(void *pkt)
{
	json_t *obj;
	return obj;
}

json_t *
pkt2json(struct hdr_pkt *pkt)
{
/*	switch(pkt->id){
            case HELLO:
                return hello2json(pkt);
	    case ACK:
                return ack2json(pkt);  
            default:        
                return NULL;
	}
        */
        return;
}



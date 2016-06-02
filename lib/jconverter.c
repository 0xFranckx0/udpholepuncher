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
	switch(pkt->id){
            case KEEPALIVE:
                return keep2json(pkt);
            case HELLO:
                return hello2json(pkt);
	    case ACK:
                return ack2json(pkt);  
	    case BYE:	
                return bye2json(pkt);
            default:        
                return NULL;
	}
}


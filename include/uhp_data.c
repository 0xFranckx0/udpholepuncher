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

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include <stdint.h>
#include "uhp.h"

int
rand2int(uint8_t *rb, int size)
{
        int res;
	for (int i = 0; i < size; ++i) { 
#if BYTE_ORDER == BIG_ENDIAN
		    res |= (rb[i] & 1) << (7 - i);
#elif BYTE_ORDER == LITTLE_ENDIAN
		    res |= (rb[i] & 1) << (i);
#endif
	}
        return res;
}

char *
msg2json(const struct punch_msg *msg)
{
	char *s = NULL;
	char *type;
	json_t *root = json_object();
	switch(msg->tag) {  
        case 0:
                type = strdup(HELLO_TAG);
                if (type == NULL){
                        perror("String duplciation failed");
                        goto error;
                }
                break;
        case 1:
                type = strdup(ACK_TAG);
                if (type == NULL){
                        perror("String duplciation failed");
                        goto error;
                }
                break;
        case 2:
                type = strdup(BYE_TAG);
                if (type == NULL){
                        perror("String duplciation failed");
                        goto error;
                }
                break;
        case 3:
                type = strdup(CANCEL_TAG);
                if (type == NULL){
                        perror("String duplciation failed");
                        goto error;
                }
                break;
        default:
                perror("Unknown message tag");
                goto error;
        }

        root = json_pack("{sssisisi}", 
                        "type", type, 
                        "punchid", msg->punchid,
                        "count", msg->count,
                        "epoch", msg->epoch);
	  
	s = json_dumps(root, 0);
	json_decref(root);

        return s;

error:
	json_decref(root);
        return NULL;
}

struct punch_msg *
json2msg(const char *s)
{
	json_t *root = json_object();
        json_error_t err;
	char *tag = NULL;
        struct punch_msg *msg = NULL;

	root = json_loads(s,0, &err);
	if (root == NULL) {
    		fprintf(stderr, "error: on line %d: %s\n", err.line, err.text);
		goto error;
	}
        msg = new_punch_msg();

	json_unpack(root, "{s:s, s:i, s:i, s:i}", 
			"type", &tag, 
			"punchid", &msg->punchid,
			"count", &msg->count,
			"epoch", &msg->epoch);
	printf("TYPE: %s\n", tag);
	if (strcmp(HELLO_TAG, tag) == 0) {
		msg->tag = HELLO;
	} else if (strcmp(CANCEL_TAG, tag) == 0){
		msg->tag = CANCEL;
	} else if (strcmp(ACK_TAG, tag) == 0) {
		msg->tag = ACK;
	} else if (strcmp(BYE_TAG, tag) == 0) {
		msg->tag = BYE;
	} else {
		goto error;
	}

	json_decref(root);
	return msg;

error:
        return NULL;
}


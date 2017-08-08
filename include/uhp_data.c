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
#include <arpa/inet.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include <stdint.h>
#include "uhp.h"

static int cmp_int(const void *, const void *);
static int str2int(char *);
static void print_data_int(void *);


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
        del_punch_msg(msg);
        return NULL;
}

struct l_ports * 
parse_ports(char **ports, int size)
{       
        struct l_ports *list_ports = NULL;
        struct slist list;
        void *data = NULL;
        int range[2];
        int i, j, n, x, diff, inf; 
	char *buf, *p;
        char *token = NULL;
        char *delim = "-";

        slist_init(&list, sizeof(int));

        for(i = 0; i < size; i++) {
                if (strchr(ports[i],'-') != NULL && 
                    (strchr(ports[i],'-') == strrchr(ports[i],'-'))){
                        /* Get the upper and lower ports of the range */
                        n = strlen(ports[i])+1;
                        j = 0;
                        /* Declare a variable-length array for strtok */
                        char tmp[n];
                        strcpy(tmp,ports[i]);
                        token = strtok(tmp,delim);
                        while (token != NULL) {
                                range[j] = str2int(token);
                                if(range[j] < 0) {
                                        perror("Failed to convert string to int");
                                        goto error;
                                }
                                token = strtok(NULL, delim);
                                j++;
                        } 
                        diff = (range[0] >= range[1])? range[0] - range[1]:
                                                       range[1] - range[0];
                        inf = (range[0] >= range[1])? range[1]:range[0];
                        for (j = 0; j <= diff; j++) { 
                                slist_insert(&list, &inf);
                                inf++;
                        }
                } else if (strchr(ports[i],'-') != NULL && 
                           (strchr(ports[i],'-') != strrchr(ports[i],'-'))) {
                        perror("BAD string");
                        goto error;
                } else {
                        x = str2int(ports[i]);
                        if(x < 0) {
                                perror("Failed to convert string to int");
                                goto error;
                        }
                	slist_insert(&list, &x);
		}
        }

        list_ports = malloc(sizeof(struct l_ports));
        if (list_ports == NULL) {
                perror("Malloc failed");
                goto error;
        }

        list_ports->p = malloc(list.len * sizeof(int));
        if (list_ports->p == NULL) {
                perror("Malloc failed");
                goto error;
        }
        list_ports->size = 0;

        for (i = 0; slist_is_empty > 0; i++) {
                data = slist_pop(&list);
                if (data != NULL) {
                        list_ports->p[i] = *((int *)data); 
                        list_ports->size++;
                } else {
                        break;
                }        
        }
        /* sort the port list in ascending order */
        qsort(list_ports->p, list_ports->size, sizeof(int), cmp_int); 

        return list_ports;

error:
        if (list_ports->p != NULL)
                free(list_ports->p);
        if (list_ports != NULL)
                free(list_ports);
        
        return NULL;

}


/* Local functions */

int 
cmp_int(const void *a, const void *b)
{
        return (*(int *)a - *(int *)b);
}

int
str2int(char *str)
{
        long lval;
        int ival;
	char *buf;

        errno = 0; 
        lval = strtol(str, &buf, 10);
        if ((errno == ERANGE && (lval == LONG_MAX || 
                lval == LONG_MIN)) || (lval > 65535 || lval < 0)){ 
                perror("#2 strtol failed");
                return -1;
        }
        ival = lval;

        return ival;
}

void
print_data_int(void *data)
{
        int c = *((int *) data); 
        if (data != NULL)
                printf("%d\n", c);
}



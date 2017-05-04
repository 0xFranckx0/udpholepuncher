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

#define MAX_BYTES 4

static void 	free_pkt(struct hdr_pkt *);
static int 	port_sanitization(char *);
static struct 	base *new_base(const char *);
static void 	free_base(struct base *);

struct base*
new_base(const char *port)
{
        /*
	struct 		base *b;
	
	b = malloc(sizeof(b));
	if (b == NULL) {
		perror("malloc()");
		goto out;
	}

	b->port = strndup(port, strlen(port) + 1);
	if (b->port == NULL){
		perror("strndup()");
		goto out;
	}
	if ( b->timestamp = (int)time(NULL) < 0 ) {
		perror("time()");
		goto out;
	}

	return b;

out:
	if (b->port != NULL)
		free(b->port);

	if (b->rand != NULL)
		free(b->rand);

	if (b != NULL)
		free(b);

	return NULL;
        */
}

void
free_base(struct base *b)
{

}

void
free_pkt(struct hdr_pkt *pkt)
{
        /*
        if(pkt != NULL){
            switch(pkt->id){
                 default:
                 break;
             }
        }
        */
}

int
port_sanitization(char *p)
{
	char buffer[33];
	int ret = snprintf(buffer, sizeof(buffer), "%d", p); 
	if (ret == -1 || ret >= sizeof(buffer)) 
		return -1;

	return 0;
}
/*
void
list_init(struct list *l, void (*destroy)(void *data))
{
	printf("list init\n");
	l->size = 0;
	l->destroy = destroy;
	l->head = NULL;
	l->tail = NULL;

}

void 
list_destroy(struct list *l)
{
	void *data;

	while(l->size > 0) {
		if (list_delete_next(l, NULL,(void **)&data) == 0 
			&& l->destroy != NULL) {
			l->destroy(data);
		}
	}
	memset(l, 0, sizeof(l));
	printf("list destroy\n");
}

int 
list_append_next(struct list *l, struct list_elem *e, const void *d)
{
	struct list_elem *new_elem;

	new_elem = malloc(sizeof(*new_elem));
	if (new_elem == NULL) {
		perror("Malloc failed");
		exit(-1);
	}
	new_elem->data = (void*)d;
	if (e == NULL) {
                if (l->size == 0)
                        l->tail = new_elem;

                new_elem->next = l->head;
                l->head = new_elem;
	}
	return 0;

}

int
list_delete_next(struct list *l, struct list_elem *e, void **d)
{

	return 0;
}
*/

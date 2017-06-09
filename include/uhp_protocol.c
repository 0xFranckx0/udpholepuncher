#include "uhp.h"

struct punch_msg *
new_punch_msg()
{
        struct punch_msg *msg;

        msg = malloc(sizeof(*msg));
        if (msg == NULL) {
                perror("Failed to allocate memory");
                exit(1);
        }

        return msg;
}
void 
del_punch_msg(struct punch_msg *msg)
{
        if ( msg != NULL ) 
                free((void*)msg);
}

struct punch_msg *
next_msg(struct transaction **table, int port)
{
        struct punch_msg *msg;
        
        if ( table[port] == NULL ) {
                msg = new_punch_msg();
                msg->tag = HELLO;
                msg->punchid = rand();
                msg->epoch = (int)time(NULL); 
                msg->count = 1;
        } else {
                msg = table[port];
        }

        return msg;
}
void
next_operation(struct transaction **table, struct punch_msg *msg, int port)
{
        if (table[port] == NULL)
                printf("NOT INITIALIZED\n");
}

void 
init_table(struct transaction **table, int s)
{
        int i;
        for (i = 0; i < s; i++)
                *(table+i) = NULL;
}

void
new_transaction(struct transaction **table, int port)
{
        struct transaction *t;

        t = malloc(sizeof(*t));
        if ( t == NULL ) {
                perror("Failed to allocate memory");
                return;
        }
        t->punchid = -1;
        t->origin  = -1;
        t->master = -1;
        t->status = -1;
        t->timestamp = -1;
        t->port_peer = -1;
        t->asymetric = -1;
        t->retry = -1;
        t->ip_peer = NULL;

        *(table+port) = t;
}

/*
void                cleanup_table(struct transaction **);
void                del_transaction(struct transaction *);
void                update_transaction(struct transaction **, int, 
                                       struct punch_msg *);
*/


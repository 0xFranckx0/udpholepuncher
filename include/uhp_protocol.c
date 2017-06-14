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
        int err;

        msg = new_punch_msg();
        if ( table[port] == NULL ) {
                msg->tag = HELLO;
                err = RAND_bytes(msg->punchid, 32);
                if ( err < 1 ) {
                        perror("Random failed");
                        del_punch_msg(msg);
                        return NULL;
                }
                msg->epoch = (int)time(NULL); 
                msg->count = 1;
        } else if ( table[port]->type == HELLO ) {
                memcpy(msg->punchid, table[port]->punchid, 32);
                msg->epoch = table[port]->timestamp;
                msg->tag = ACK;
                msg->count = 1;
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
                table[i] = NULL;
}

void
new_transaction(struct transaction **table, int port)
{
        struct transaction *t;
        int i;

        t = malloc(sizeof(*t));
        if ( t == NULL ) {
                perror("Failed to allocate memory");
                return;
        }
        memset(t->punchid,0,32);
        for (i = 0; i < 32; i++) 
                fprintf(stdout,"%i",t->punchid[i]);
        printf("\n");        
        t->type = -1;
        t->origin  = -1;
        t->master = -1;
        t->status = -1;
        t->timestamp = -1;
        t->retry = -1;

        table[port] = t;
        for (i = 0; i < 32; i++) 
                fprintf(stdout,"%i",table[port]->punchid[i]);
        printf("\n");        
}

void 
del_transaction(struct transaction *t)
{
        if ( t != NULL ) {
                free((void*)t);
                t = NULL;
        }
}

void 
update_transaction(struct transaction **table, int p, struct punch_msg *m)
{
        switch (m->tag) {
                case HELLO: 
                        break;
                case ACK: 
                        break;
                case BYE: 
                        break;
       }
}
/*
void                cleanup_table(struct transaction **);
*/


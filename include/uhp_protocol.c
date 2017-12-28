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
        uint8_t r[MAX_BYTES];

        msg = new_punch_msg();
        if ( table[port] == NULL ) {
                msg->port = port;
                msg->tag = HELLO;
                err = RAND_bytes(r, MAX_BYTES);
                if ( err < 1 ) {
                        perror("Random failed");
                        del_punch_msg(msg);
                        return NULL;
                }
                msg->punchid = rand2int(r, MAX_BYTES);
                msg->epoch = (int)time(NULL); 
                msg->count = 1;
        } else if ( table[port]->type == HELLO ) {
                memcpy(msg->punchid, table[port]->punchid, MAX_BYTES);
                msg->epoch = table[port]->timestamp;
                msg->tag = ACK;
                msg->count = 1;
        } else if ( table[port]->type == ACK ) {
                memcpy(msg->punchid, table[port]->punchid, MAX_BYTES);
                msg->epoch = table[port]->timestamp;
                msg->tag = BYE;
                msg->count = 1;
        }

        return msg;
}

int
next_operation(struct transaction **table, struct punch_msg *msg, int port)
{
        if (table[port] == NULL) {
                return INIT_TABLE;
        } else if (msg->tag == table[port]->type) {
                return NEXT_MESSAGE;
        } else if (msg->tag < table[port]->type) {
                return MARK_DIRTY;
        } else if (msg->tag > table[port]->type) {
                return UPDATE_TABLE_WITH_MESSAGE;
        } else {
               return END_OF_OPERATIONS; 
        }
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
        memset(t->punchid,0,MAX_BYTES);
        t->type = -1;
        t->status = -1;
        t->timestamp = -1;
        t->retry = -1;

        table[port] = t;
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
update_transaction(struct transaction **table, int p, 
                struct punch_msg *m, int op)
{
        switch (op) {
                
                case UPDATE_TABLE_WITH_MESSAGE: 
                        memcpy(table[p]->punchid, m->punchid, MAX_BYTES);
                        table[p]->type = m->tag;
                        table[p]->timestamp = m->epoch;
                        table[p]->status = PENDING;
                        table[p]->retry = m->count;
                        break;

                case MARK_DIRTY:
                        break;

                case MARK_RETRANSMIT:
                        break;

                default:
                        break;
       }
}
void 
cleanup_table(struct transaction **table, int s)
{
        int i;

        for (i = 0; i < s; i++) 
                del_transaction(table[i]);
}


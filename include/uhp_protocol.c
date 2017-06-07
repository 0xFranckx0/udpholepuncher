#include "uhp.h"

void 
init_table(struct transaction **table, int s)
{
        int i;
        for (i = 0; i < s; i++)
                *(table+i) = NULL;
}

void
next_operation(struct transaction **table, struct punch_msg *msg, int port)
{
}


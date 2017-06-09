#include <stdio.h>

#include <include/uhp.h>

int
main()
{
        struct transaction *transac_table[MAX_PORT];
        struct punch_msg *pm = NULL;
        int i;

        init_table(transac_table, MAX_PORT);

        /*
        for (i = 0; i < MAX_PORT; i++) {
                if ( transac_table[i] == NULL)
                        printf("NOT INITIALIZED\n");
        }
        */

        //next_operation(transac_table, &pm, 2);
        pm = next_msg(transac_table, 2222);
        printf("TAG = %d\nPUNCHID = %d\nEPOCH = %d\nSEQ = %d\n",
                        pm->tag, pm->punchid, pm->epoch, pm->count);
        del_punch_msg(pm);
        new_transaction(transac_table, 2222);
        printf("punchid = %d\n", transac_table[2222]->punchid);

        return 0;
}
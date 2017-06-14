#include <stdio.h>
#include <openssl/rand.h>

#include <include/uhp.h>

int
main()
{
        struct transaction *transac_table[MAX_PORT];
        struct punch_msg *pm = NULL;
        int i, err;
        uint32_t id;
        unsigned char buf[32], *b;
        char *e_str;

        init_table(transac_table, MAX_PORT);

        for (i = 0; i < MAX_PORT; i++) {
                if ( transac_table[i] == NULL)
                        printf("NOT INITIALIZED\n");
        }

        //next_operation(transac_table, &pm, 2);
        /*
        pm = next_msg(transac_table, 2222);
        printf("TAG = %d\nPUNCHID = %ld\nEPOCH = %d\nSEQ = %d\n",
                        pm->tag, pm->punchid, pm->epoch, pm->count);
        del_punch_msg(pm);
        */
        //memset(buf,1,32);
        new_transaction(transac_table, 2222);
        for (i = 0; i < 32; i++) 
                fprintf(stdout,"%i",transac_table[2222]->punchid[i]);
        printf("\n");        
        /*
        printf("punchid = %s\nType = %d\nOrigin = %d\nMaster = %d\n ",
                transac_table[2222]->punchid, transac_table[2222]->type,
                transac_table[2222]->origin, transac_table[2222]->master);
       */
       // printf("BUF: %c\n", transac_table[2222]->punchid[0]);
       b64_encode((const unsigned char *)transac_table[2222]->punchid,
                       32,&e_str);
       if (e_str != NULL)
               printf("%s\n", e_str);

        //b64_decode(e_str, &b, 32);
        //for (i = 0; i < 32; i++) 
        //        fprintf(stdout,"%i",buf[i]);
        //printf("\n");        
        del_transaction(transac_table[2222]);        

        return 0;
}

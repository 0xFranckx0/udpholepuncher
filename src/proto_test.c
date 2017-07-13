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
        unsigned char buf[MAX_BYTES];
        uint16_t  **b;
        uint8_t bu[MAX_BYTES];
        char *e_str;
    	int res = 0;

        init_table(transac_table, MAX_PORT);
/*
        for (i = 0; i < MAX_PORT; i++) {
                if ( transac_table[i] == NULL)
                        printf("NOT INITIALIZED\n");
        }
*/
        //next_operation(transac_table, &pm, 2);
        RAND_bytes(bu, MAX_BYTES);
	for (int i = 0; i < MAX_BYTES; ++i) { 
#if BYTE_ORDER == BIG_ENDIAN
		    res |= (bu[i] & 1) << (7 - i);
#elif BYTE_ORDER == LITTLE_ENDIAN
		    res |= (bu[i] & 1) << (i);
#endif
	}
	printf("%d\n",res);
     //   pm = next_msg(transac_table, 2222);
//        printf("%d", pm->punchid);
        /*
        for (i = 0; i < MAX_BYTES ; i++)
                printf("%i", pm->punchid[i]);
        printf("\n");        
        */
/*        b64_encode((const uint16_t *)pm->punchid,MAX_BYTES,&e_str);
        if (e_str != NULL)
               printf("%s\n", e_str);
        new_transaction(transac_table, 2222);
        memcpy(transac_table[2222]->punchid,  pm->punchid, MAX_BYTES);
  */      //RAND_bytes(transac_table[2222]->punchid,32);
/*        b64_encode((const unsigned char*)transac_table[2222]->punchid,MAX_BYTES,&e_str);
        if (e_str != NULL)
               printf("%s\n", e_str);

        b64_decode(e_str, b, MAX_BYTES);
        fprintf(stdout,"%d", *b);
  */      /*
        for (i = 0; i < MAX_BYTES; i++) 
                fprintf(stdout,"%i", b[i]);
        printf("\n");        
        */
    /*    del_transaction(transac_table[2222]);        
        del_punch_msg(pm);
*/
        return 0;
}

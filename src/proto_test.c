#include <stdio.h>
#include <openssl/rand.h>

#include <include/uhp.h>

int
main()
{
        /*
        struct transaction *transac_table[MAX_PORT];
        struct punch_msg *pm = NULL;
        struct punch_msg *resp = NULL;
        int i, err;
        uint32_t id;
        unsigned char buf[MAX_BYTES];
        uint16_t  **b;
        uint8_t bu[MAX_BYTES];
        char *e_str;
    	int res = 0;
        char *json;
        */

/*
        init_table(transac_table, MAX_PORT);
        for (i = 0; i < MAX_PORT; i++) {
                if ( transac_table[i] == NULL)
                        printf("NOT INITIALIZED\n");
        }
*/
        //next_operation(transac_table, &pm, 2);
//        RAND_bytes(bu, MAX_BYTES);
//        res = rand2int(bu, MAX_BYTES);
//	printf("%d\n",res);
/*
        pm = next_msg(transac_table, 2222);
        printf("%d\n", pm->punchid);
        json = msg2json(pm);
        if (json == NULL) {
                perror("JSON ERROR");
                exit(1);
        }
        printf("%s\n", json);
	resp = json2msg(json);
        if (resp == NULL) {
                perror("RESP ERROR");
                exit(1);
        }
        printf("TAG: %d\n", resp->tag);
        printf("PUNCHID: %d\n", resp->punchid);
        printf("EPOCH: %d\n", resp->epoch);
        printf("COUNT: %d\n", resp->count);
*/		
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

        
        struct l_ports *ports; 
        int i;

        ports = parse_ports("%s","32", "40");
        if(ports == NULL){
                perror("ports error");
                exit(0);
        }
        for(i = 0; i < ports->size; i++)
                printf("%d\n", ports->p[i]);
        
        return 0;
}

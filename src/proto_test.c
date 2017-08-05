#include <stdio.h>
#include <openssl/rand.h>

#include <include/uhp.h>

static void print_data_int(void *);

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
/* tests for split port strings 

        struct l_ports *ports; 
        int i;

        ports = parse_ports(2, "40", "41-50");
        if(ports == NULL){
                perror("ports error");
                exit(0);
        }
        for(i = 0; i < ports->size; i++)
                printf("%d\n", ports->p[i]);
        
*/

/* Tests for strings */
        struct slist list;
        int data[10] = {5060, 22, 132, 3333, 40, 2, 50, 6};
        int i;
        int a = 12;
        int b = 13;

        slist_init(&list);
        for (i = 0; i < 8; i++) 
                slist_insert(&list, &data[i]);
                
        slist_print(&list, print_data_int);
        

        slist_insert(&list, &a);
        slist_append(&list, &b);
        printf("\n\n\n");
        slist_print(&list, print_data_int);

        return 0;
}

void
print_data_int(void *data)
{
        int c = *((int *) data); 
        if (data != NULL)
                printf("%d\n", c);
}

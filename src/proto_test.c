#include <stdio.h>
#include <openssl/rand.h>

#include <include/uhp.h>

static void print_data_int(void *);
static int comp_data_int(void *, void *);
static void delete_data_int(void *);

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
/* tests for split port strings */ 

/*
        struct l_ports *ports; 
        int i;
        char *port_str[2] = {"6535", "40-50"};

        ports = parse_ports(port_str, 2);
        if(ports == NULL){
                perror("ports error");
                exit(0);
        }

        printf("---42:  %d\n", ports->size);
        
        for(i = 0; i < ports->size; i++)
                printf("INT %d, STR = %s\n", ports->p[i], (ports)->p_str[i]);
*/
        

/* Tests for LISTS */
/*
        struct slist list;
        struct entry *tmp = NULL;
        int data[10] = {5060, 22, 132, 3333, 40, 2, 50, 6};
        int i, x;
        int a = 12;
        int b = 13;
        int c = 132;

        slist_init(&list, sizeof(int));
        if (slist_is_empty(&list) > 0) {
                printf("NOT EMPTY\n");
        } else {
                printf("EMPTY\n");
        }
        for (i = 0; i < 8; i++) 
                slist_insert(&list, &data[i]);
                
        slist_print(&list, print_data_int);
        

        slist_insert(&list, &a);
        if (slist_is_empty(&list) > 0) {
                printf("NOT EMPTY\n");
        } else {
                printf("EMPTY\n");
        }
        printf("\n---------\n");
        slist_print(&list, print_data_int);
        x = entry_find(&list, comp_data_int, &c);
        printf("x = %d\n", x);
        tmp = entry_get(&list, comp_data_int, &c);
        entry_delete(&list, NULL, tmp);
        slist_pop(&list);
        printf("\n---------\n");
        slist_print(&list, print_data_int);
*/
/* Test For initializing sockets */
        struct l_ports *ports; 
        struct input_p **ip;
        int i;
        char *port_str[2] = {"6535", "40-50"};
        char *address = "10.30.40.50";  

        ports = parse_ports(port_str, 2);
        if(ports == NULL){
                perror("ports error");
                exit(0);
        }

        ip = malloc(ports->size * sizeof(struct input_p)); 
        if(ip == NULL){
                perror("ports error");
		goto freemem;
        }

        for(i = 0; i < ports->size; i++){
                ip[i] = malloc(sizeof(struct input_p)); 
                if(ip[i] == NULL){
                        perror("Malloc error");
			goto freemem;
                }
		ip[i]->address = strdup(address);	
		if (ip[i]->address == NULL){
			perror("strdup failed");
			goto freemem;
		}
		ip[i]->port_int = ports->p[i];
		ip[i]->port = ports->p_str[i];

		ip[i]->msg = strdup("HELLO");	
		if (ip[i]->msg == NULL){
			perror("strdup failed");
			goto freemem;
		}
		printf("INITIALIZATION: MSG: %s\n", ip[i]->msg);

		ip[i]->base = event_base_new();
		if (ip[i]->base == NULL) {
			perror("Couldn't open event base");
			goto freemem;
		}
		printf("INITIALIZATION: ADDRESS: %s PORT: %d - %s\n",
			ip[i]->address, ip[i]->port_int, ip[i]->port);
	}

freemem:
	/* Freeing memory */
	if (ip != NULL && ports != NULL) {
		for(i = 0; i < ports->size; i++){
			if (ip[i] != NULL){
				if(ip[i]->address != NULL)
					free(ip[i]->address);
				if(ip[i]->msg != NULL)
					free(ip[i]->msg);
			}
			if(ports->p_str != NULL && ports->p_str[i] != NULL)
				free(ports->p_str[i]);
		}

		free(ip);
		if(ports->p != NULL)
			free(ports->p);
		if(ports->p_str != NULL)
			free(ports->p_str);
			
		free(ports);
	}	

        return 0;
}

void
print_data_int(void *data)
{
        int c = *((int *) data); 
        if (data != NULL)
                printf("%d\n", c);
}

int
comp_data_int(void *x, void *y)
{
        return((*((int*)x) == *((int*)y)) ? 0 : 1);        
}

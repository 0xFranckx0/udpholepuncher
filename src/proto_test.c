#include <config.h>
#include <ctype.h>
#include <event.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/rand.h>

#include <include/punch.h>

#include <include/uhp.h>

#define MAX_BUF		64000

static void print_data_int(void *);
static int comp_data_int(void *, void *);
static void delete_data_int(void *);
/*static int p_cb(int, struct uhp_carrier *);*/
static void usage();

int
main (int argc, char **argv)
{

	struct event_base 	*base; 
	char 			*port;
	char 			*pt[1];
	char 			*message, *msg;
	char 			*address, *adr;
	int			 c;
	int			 options = 0;

	struct uhp_carrier      *data;
	struct entry	        *e;
        struct slist            *it = NULL;
        char                    *port_str[2] = {"6527", "4001"};
        /*char                    *address = "10.30.40.50";*/  
	/*char		        *message = "PUNCHED FROM: ";*/
	char buf[MAX_BUF];
	int		 i;
	int len;
	ssize_t lenrcv, lensnd;
	socklen_t slen = sizeof(struct sockaddr_in);

	printf("INITIALIZATION\n");

	while ((c = getopt(argc, argv, ":a:m:p:")) != -1) {
		switch (c) {
		case 'a':
			printf("Setting a \n");
			address = optarg;
			options++;
			break;
		case 'p':
			printf("Setting p \n");
			port = optarg;
			options++;
			break;
		case 'm':
			printf("Setting m \n");
			msg = optarg;
			options++;
			break;
		default:
			usage();
			exit(-1);
		}
	}
	if (options != 3) {
		usage();
		exit(-1);
	}
        pt[0] = strdup(port);
	if (pt[0] == NULL){
		perror("strdup failed");
		exit(-1);
	}
        adr = strdup(address);
	if (adr == NULL){
		perror("strdup failed");
		exit(-1);
	}
        message = strdup(msg);
	if (message == NULL){
		perror("strdup failed");
		exit(-1);
	}
	len = strlen(message) + 1;

	if ((it = punch_init(pt, 1, address)) 
                        == NULL) {
                perror("Punch init failed");
                return -1;
        }
        struct uhp_carrier out = {
                .items = it,
                .list_evts = NULL,
                .data_punch = NULL,
                .metadata = NULL
        };

        out.list_evts[0] = malloc(it->len * sizeof(struct event *));
        if (out.list_evts[0] == NULL){
                perror("Malloc failed in punch_init");
        }

        out.list_evts[1] = malloc(it->len * sizeof(struct event *));
        if (out.list_evts[1] == NULL){
                perror("Malloc failed in punch_init");
        }

        if (( base = event_base_new()) == NULL) {
                perror("Failed to create event");
                exit(-1);
        }

        punch_start(&out, base);
        event_base_dispatch(base);
/*        

        for (i = 0; slist_is_empty(it) > 0; i++) {
		printf("NB items = %d\n", it->len);
		data = (struct uhp_data *)slist_pop(it);
		if (data != NULL) {
			sock_free(data->in);
			free(data);
		}
                event_free(out.list_evts[0][i]);
                event_free(out.list_evts[1][i]);
        }	
        event_base_free(base);
        

        
	if (lensnd = (sendto((int)out.data_punch->sock, (const void *)msg, 
			len , 0, (struct sockaddr *) out.data_punch->sin, 
			slen)) < 0 ) {

	        perror("sendto()");
		goto cleanup;
        }


	memset(buf,0,MAX_BUF);

	if (lenrcv = (recvfrom((int)out.data_punch->sock, &buf, sizeof(buf) - 1, 
			0, (struct sockaddr *) &out.data_punch->sin, 
			&slen)) == -1) {

		perror("recvfrom()");
		goto cleanup;
	}

	printf("SERVER RECEIVED : %s at address : \n", buf, 
		out.data_punch->address);
*/
cleanup:
        sock_free(out.data_punch);
	return 0;
}
/*
int
p_cb(int flag, struct uhp_info *ui)
{
	
	return 0;
}
*/
void 
usage(){
	printf("Usage: ");
	printf("test -a 192.168.0.1 -p 54321 -m message\n");
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

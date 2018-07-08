#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <include/punch.h>
#include <include/uhp.h>

static void print_string(void *);
static int comp_string(void *, void *);
static void usage();

int
main (int argc, char **argv)
{
	int			 c, res;
	int			 options = 0;
	char 			*address;
	char 			*port, *tmp;
	char 			*msg;
	char			*ports[2];
	struct slist		 list;

	printf("INITIALIZATION\n");

	while ((c = getopt(argc, argv, ":a:m:p:")) != -1) {
		switch (c) {
		case 'a':
			address = optarg;
			options++;
			break;
		case 'p':
			port = optarg;
			options++;
			break;
		case 'm':
			msg = optarg;
			options++;
			break;
		default:
			usage();
			exit(-1);
		}
	}

	ports[0] = strdup(port);
	if(ports[0] == NULL){
		perror("Error strdup(ports)");
		goto error;
	}
	ports[1] = strdup(address);
	if(ports[1] == NULL){
		perror("Error strdup(address)");
		goto error;
	}
	ports[2] = strdup(msg);
	if(ports[2] == NULL){
		perror("Error strdup(msg)");
		goto error;
	}


	slist_init(&list, sizeof(char*));
	slist_insert(&list, ports[0]);
	slist_insert(&list, ports[1]);
	slist_insert(&list, ports[2]);
	if (res = entry_find(&list,comp_string, ports[2]) == 0)
		printf("%s matched\n", ports[2]);

	printf("-------\n");
	slist_print(&list, print_string);	
	printf("-------\n");

	while (slist_is_empty(&list) > 0 ){
		printf("%s\n", (char*) slist_pop(&list));
	}
	
	free(ports[0]);
	free(ports[1]);
	free(ports[2]);

	return 0;

error:
	if (ports[0])
		free(ports[0]);

	return -1;
}

void 
usage(){
	printf("Usage: ");
	printf("test -a 192.168.0.1 -p 54321 -m message\n");
}

int
comp_string(void *a, void *b){
	return strcmp((char *)a, (char *)b);
}

void
print_string(void *s)
{
	printf("%s\n", (char *)s);
}

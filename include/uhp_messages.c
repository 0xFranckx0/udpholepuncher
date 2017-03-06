#include "uhp.h"

json_t	*
new_hello(struct uhp_socks *s)
{
	json_t *hello = json_object();
	unsigned long err;
	int rc;

	byte buffer[32];

	rc = RAND_bytes(buffer, sizeof(buffer));
	err = ERR_get_error();
	if(rc != 1) {
		exit(-1);
    	/* RAND_bytes failed */
    	/* `err` is valid    */
	}

	json_object_set_new( hello, "punchid", json_integer( 1 ) );
	json_object_set_new( hello, "portorigin", json_string("enable") );
	json_object_set_new( hello, "ip", json_string( 0 ));
	json_object_set_new( hello, "count", json_integer( 0 ));
	json_object_set_new( hello, "mastercandidate", json_string( 0 ));

	return hello;
}

void
free_message(json_t *json)
{
	json_decref(json);
}

/*
void
free_hello(json_t *j)
{
}

json_t *
new_ack(void)
{
}
void
free_ack(json_t *)
{
}
json_t *
new_bye(void)
{
}
void
free_bye(json_t *)
{
}
*/

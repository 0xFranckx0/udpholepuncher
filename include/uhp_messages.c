#include "uhp.h"

json_t*
new_msg(struct punch_msg *m)
{
	json_t *msg = json_object();

	json_object_set_new( msg, "type", json_string(m->tag) );
	json_object_set_new( msg, "punchid", json_integer(m->punchid) );
	json_object_set_new( msg, "count", json_integer( m->count ));
	json_object_set_new( msg, "epoch", json_string( m->epoch ));

	return msg;
}

void
free_message(json_t *json)
{
        if (json != NULL)
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

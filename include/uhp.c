/*
 * =============================================================================
 *
 *       Filename:  uhp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/28/2016 06:48:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Franck Rupin (), franck.rupin@gmail.com
 *        Company:  
 *
 * =============================================================================
 */

#include <include/uhp.h>

struct uhp_info *
punch(const char *address, const char *port)
{
	struct uhp_info *infos = NULL;
	struct uhp_socks s;

	s.dst = strdup(address);
	if (s.dst == NULL){
		syserr(__func__, "strdup");
		goto cleanup ;
	}
	s.rport = strdup(port);
	if (s.rport == NULL){
		syserr(__func__, "strdup");
		goto cleanup;
	}

	infos = malloc(sizeof(infos));
	if (infos == NULL){
		syserr(__func__, "malloc");
		goto cleanup;
	}


cleanup:
	if (s.rport != NULL)
		free(s.rport);
	if (infos != NULL)
		free(infos);

	return infos;
}

/*
    libuhp is a library dedicated to hole punching NAT traversal over UDP
    Copyright (C) <2016>  <Franck Rupin franck@holepuncher.io>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


    <libuhp>  Copyright (C) <2016>  <Franck Rupin>
    This program comes with ABSOLUTELY NO WARRANTY.
    This is free software, and you are welcome to redistribute it
    under certain conditions.
*/

#include "punch.h"

struct uhp_info *
punch(const char *address, const char *port, const char *msg)
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
	if (s.dst != NULL)
		free(s.dst);

	if (s.rport != NULL)
		free(s.rport);

	if (infos != NULL)
		free(infos);

	return infos;
}

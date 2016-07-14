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

#include <unistd.h>
#include <openssl/rand.h>

#include <include/uhp.h>

#include "uhp_utils.h"


unsigned char*
uhp_rand(int s)
{
	unsigned char *rands;
	rands = malloc(sizeof(rand)*s);
	if (rands == NULL){
		perror("malloc()");
		goto error;
	}
	
	if( !(RAND_bytes(rands, s))) {
		perror("ERROR: call to RAND_pseudo_bytes() failed\n");
		goto error;
	} 

	return rands;
	
error:
	if (rands != NULL)
		free(rands);
	retun NULL;
}

int
uhp_rand_seed(int s)
{
	if(!RAND_load_file("/dev/random", s)){
		perror("NOT enought entropy with RAND\n");
		return -1;
	}  
	return RAND_status();
}


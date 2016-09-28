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

#if defined(HAVE_DEVRAND) || defined(HAVE_DEVURAND)
static int 	__uhp_rand(const char*, unsigned char*, int);
#endif /* HAVE_DEVRAND... */

#if defined(HAVE_DEVRAND) || defined(HAVE_DEVURAND)
int
__uhp_rand(const char *device, unsigned char *byte, int blen)
{
	int fd;
	ssize_t noc;

	fd = open(device, O_RDONLY);
	if (fd < 0) {
		perror("open()");
		return -1;
	}
	noc = read(fd, (void *) byte, blen);
	if (noc < 0) {
		perror("read()");
		(void) close(fd);
		return -1;
	}
	if (noc != blen) {
		printf("read %zd != %zu bytes", noc, blen);
		(void) close(fd);
		return -1;
	}
	(void) close(fd);
	return 0;
}
#endif /* HAVE_DEVRAND... */

unsigned char*
uhp_rand(int s)
{
	unsigned char *rands;
	int nb;
	rands = malloc(sizeof(rand)*s);
	if (rands == NULL){
		perror("malloc()");
		goto error;
	}

	if( (nb = (RAND_bytes(rands, s))) < 0 ) {
		perror("ERROR: call to RAND_bytes() failed\n");
#if defined(HAVE_DEVURAND)
		else if ( (nb = __uhp_rand("/dev/urandom", rand, s)) > 0 )
			goto out;
#elif defined(HAVE_DEVRAND)
		else if ( (nb = __uhp_rand("/dev/random", rand, s)) > 0 )
			goto out;
#else
	goto error;
#endif /* HAVE_DEVRAND... */	
	}
		
error:
	if (rands != NULL)
		free(rands);
	return NULL;

out:
	return rands;
}

int
uhp_rand_seed(int s)
{

#if defined(HAVE_DEVURAND)
	if (RAND_load_file("/dev/urandom", s) > 0)
		return RAND_status();
/*#endif  HAVE_DEVURAND... */
#elif defined(HAVE_DEVRAND)
	if (RAND_load_file("/dev/random", s) > 0)
		return RAND_status();
#else
	for (int i = 0; (i < 3); i++) {
		uint8_t buf[4];

		if (RAND_bytes(buf, sizeof(buf)) == 0)
			continue;
		else {
			RAND_seed((const void *) buf, sizeof(buf));
			return RAND_status;
		}
	}

#endif /* HAVE_DEVRAND... */		

	return -1;
}


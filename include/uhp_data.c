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

#include <stdio.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include <stdint.h>
#include "uhp.h"

#define MAX_BYTES 4


int
port_sanitization(char *p)
{
	char buffer[33];
	int ret = snprintf(buffer, sizeof(buffer), "%d", p); 
	if (ret == -1 || ret >= sizeof(buffer)) 
		return -1;

	return 0;
}

int 
b64_encode(const unsigned char *b, size_t l, char **s) 
{ 
	BIO *bio, *b64;
	BUF_MEM *buf;
        int err;

	b64 = BIO_new(BIO_f_base64());
        if (b64 == NULL) {
                perror("BIO allocation failed");
                return 1;
        }

	bio = BIO_new(BIO_s_mem());
        if (bio == NULL) {
                perror("BIO allocation failed");
	        BIO_free(b64);
                return 1;
        }
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); 
	err = BIO_write(bio, buf, l);
        if ( err == 0 || err == -1 ) {
                perror("No data written");
	        BIO_free_all(bio);
        } else if ( err == -2 ) {
                perror("the operation is not implemented");
	        BIO_free_all(bio);
                return 1;
        }

	err = BIO_flush(bio);
        if ( err < 1 ) {
                perror("Unable to flush the BIO");
	        BIO_free_all(bio);
                return 1;
        }
	BIO_get_mem_ptr(bio, &buf);
	BIO_set_close(bio, BIO_NOCLOSE);
	BIO_free_all(bio);

	*s = (*buf).data;

	return 0; 
}



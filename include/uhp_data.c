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
         
        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, bio);
        BIO_write(b64, b, l);
        BIO_flush(b64);
        BIO_get_mem_ptr(b64, &buf);
                 
        *s = (char *)malloc(buf->length);
        if (*s == NULL) {
                perror("Malloc failed");
                return 1;
        }

        memcpy(*s, buf->data, buf->length-1);
        s[buf->length-1] = 0;

        BIO_free_all(b64);

        return 0; 
}


int
b64_decode(char *s, unsigned char **b, size_t l) 
{ 
	BIO *b64, *bio;
	int i;

	*b = malloc(l);
	memset(b, 0, l);
	 
	b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	bio = BIO_new_mem_buf(s, l);
	//bio = BIO_push(b64, bio);
	BIO_push(b64, bio);
	 
	BIO_read(bio, *b, l);
	 
	BIO_free_all(bio);

	return (0); 
}


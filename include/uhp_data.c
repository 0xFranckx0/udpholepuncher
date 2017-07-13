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
rand2int(uint8_t *rb, int size)
{
        int res;
	for (int i = 0; i < size; ++i) { 
#if BYTE_ORDER == BIG_ENDIAN
		    res |= (rb[i] & 1) << (7 - i);
#elif BYTE_ORDER == LITTLE_ENDIAN
		    res |= (rb[i] & 1) << (i);
#endif
	}
        return res;
}


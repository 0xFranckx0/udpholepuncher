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


#ifndef PUNCP_H
#define PUNCH_H

#include "uhp.h"

/**
 * \struct uhp_info
 * \brief uhp_info is the struct returned by libuhp to the caller program once
 *	  a NAT was punched and provides informations about socket, master role
 *	  and the port to reach.
 *
 */
struct uhp_info {
	int 	 	 sock;	/*!< Socket on which communication is enabled */
	char 		*port;	/*!< Destination port */
	char 		*dst;	/*!< Destination address */
	uint8_t  	 master;/*!< Defines a master */

};


struct uhp_info		*punch(const char*, const char*, const char*);

#endif /* PUNCH_H  */

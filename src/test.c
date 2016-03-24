/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/24/2016 18:150:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Franck Rupin, franck.rupin@gmail.com
 *
 * =====================================================================================
 */

#include <config.h>
#include <stdio.h>

#include <lib/uhp.h>

int
main (void)
{
          puts ("This is :" PACKAGE_STRING ".");
          uhp_new();
          uhp_print();
          return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  teststack.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  1/23/2024 7:25:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

bool upordown(int *other) {
	int x;
	
	if (!other) {
		return (upordown(&x));
	}
	return (&x > other);
}



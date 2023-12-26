/*
 * =====================================================================================
 *
 *       Filename:  flmem.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/23 22:44:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fatmeat (), pathofyggdrasil@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef FLMEM_H
# define FLMEM_H

# include "fltype.h"

namespace fl {

/*
 *	DESCRIPTION
 *		the function copy n bytes of memory from src to dest 
 *	RETURN VALUE
 *		return dest poi32er
 * */
static inline void*
memCpy(const void *dest, const void *src, u64 size) {
	while (size--) {
		*((i8 *)dest + size) = *((i8 *)src + size);
	}
	return ((void *)dest);
}

/*
 *	DESCRIPTION
 *		the function copy n bytes of memory from src to dest.
 *	RETURN VALUE
 *		returns a poi32er to the memory area (dest + n).
 *
 * */
static inline void
*memPCpy(const void *dest, const void *src, u64 n) {
	for (u64 i = 0; i < n; i++) {
		*((i8*)dest + i) = *((i8 *)src + i);
	}
	return ((i8 *)dest + n);
}

/*
 *	DESCRIPTION
       The  function fills the first n bytes of the memory area poi32ed to by mem with
       the constant byte b.

	RETURN VALUE
       The function returns a poi32er to the memory area s.
 * */
static inline void
*memSet(const void *mem, i32 b, u64 n) {
	for (u64 i = 0; i < n; i++) {
		*((i8 *)mem + i) = b;
	}
	return ((void *)mem);
}

/*
 *	DESCRIPTION
 *		allocate a new memory chunk of n bytes and copy n byte of mem to new chunk
 *	RETURN VALUE
 *		return the new memory chunk
 *
 * */
static inline void
*memDup(const void *mem, u64 n, void*(*allocator)(u64)) {
	void	*dup;
	dup = allocator(n);
	while (n--) {
		*((i8*)dup + n) = *((i8 *)mem + n);
	}
	return (dup);
}

/*
 *	DESCRIPTION
 *		compare two i8 * data
 *	RETURN VALUE
 *		return the substraction of the two last i8 i8
 *
 * */
static inline i32
memCmp(const void *mem1, const void *mem2, u64 n) {
	i8 span;
	while (n--) {
		span = *((i8 *)mem1 + n) - *((i8 *)mem2 + n);
		if (span != 0)
			return (span);
	}
	return (span);
}

};

# endif


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

/*
 *	DESCRIPTION
 *		the function copy n bytes of memory from src to dest 
 *	RETURN VALUE
 *		return dest pointer
 * */
inline void*
flMemCpy(const void *dest, const void *src, unsigned long long size) {
	while (size--) {
		*((char *)dest + size) = *((char *)src + size);
	}
	return ((void *)dest);
}

/*
 *	DESCRIPTION
 *		the function copy n bytes of memory from src to dest.
 *	RETURN VALUE
 *		returns a pointer to the memory area (dest + n).
 *
 * */
inline void
*flMemPCpy(const void *dest, const void *src, unsigned long long n) {
	for (unsigned long long i = 0; i < n; i++) {
		*((char*)dest + i) = *((char *)src + i);
	}
	return ((char *)dest + n);
}

/*
 *	DESCRIPTION
       The  function fills the first n bytes of the memory area pointed to by mem with
       the constant byte b.

	RETURN VALUE
       The function returns a pointer to the memory area s.
 * */
inline void
*flMemSet(const void *mem, int b, unsigned long long n) {
	for (unsigned long long i = 0; i < n; i++) {
		*((char *)mem + i) = b;
	}
	return ((void *)mem);
}

/*
 *	DESCRIPTION
 *		allocate a new memory chunk of n bytes and copy n byte of mem to new chunk
 *	RETURN VALUE
 *		return the new memory chunk
 *
 *	note
 *		need stdlib.h for malloc function
 *
 *		if you want to use this function you need to define FL_USE_STDLIB_DEP before the include
 * */
inline void
*flMemDup(const void *mem, unsigned long long n, void*(*allocator)(unsigned long long)) {
	void	*dup;
	dup = allocator(n);
	while (n--) {
		*((char*)dup + n) = *((char *)mem + n);
	}
	return (dup);
}

# endif


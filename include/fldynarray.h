#ifndef FLDYNARRAY_H
# define FLDYNARRAY_H

# include <stdlib.h>
# include "fltype.h"
# include "flmem.h"

#define ALLOC_ERROR -4

typedef struct array_info_s {
	u64 size;//inbits it count the array_info_t
	u64 capacity;//inbits it count the array_info_t
	void *(*allocator)(u64);
	void (*dealloc)(void *);
} array_info_t;

inline u64 dyn_size(void *array) {
	return (*(u64 *)array);
}

inline u64 dyn_cap(void *array) {
	return (*((u64 *)array + 1));
}

inline u64 conv_size(void *array, const u8 typesize) {
	return ((*(u64 *)array - sizeof(array_info_t)) / typesize);
}

inline u64 conv_cap(void *array, const u8 typesize) {
	return ((*((u64 *)array + 1) - sizeof(array_info_t)) / typesize);
}

inline void *get_alloc(void *array) {
	return ((u64 *)array + 2);
}

inline void *get_dealloc(void *array) {
	return ((u64 *)array + 3);
}

inline i32 dyn_expand(void *array) {
	void *(*alloc)(u64) = (void *(*)(u64))get_alloc(array);

	void *newdata = alloc(dyn_cap(array) * 2 - sizeof(array_info_t));
	if (newdata == NULLPTR) {
		return (ALLOC_ERROR);
	}
	memCpy(newdata, array, dyn_size(array));
	void (*dealloc)(void *) = (void (*)(void *))get_dealloc(array);
	dealloc(array);
	array = newdata;
	*((u64 *)array + 1) = dyn_cap(array) * 2 - sizeof(array_info_t);
	return (0);
}

//add data at the end of array, you need to specify the size of data chunk in bits
inline void dyn_add(void *data, void *array, const u64 size) {
	u64 idx = dyn_size(array);

	while (size + idx >= dyn_cap(array)) {
		if (dyn_expand(array) == ALLOC_ERROR) {
			abort();
		}
	}
	memCpy((u64 *)array + idx, data, size);
	*(u64 *)array += size;
}

//don't use array after this, it erase all of it
inline void dyn_clear(void *array) {
	void (*dealloc)(void *) = (void (*)(void *))get_dealloc(array);
	dealloc(array);
}

#endif

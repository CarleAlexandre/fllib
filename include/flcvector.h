#ifndef FL_C_VECTOR_H
# define FL_C_VECTOR_H

typedef unsigned long long u64;

typedef union s_array {
	void *ptr;
	char *data;
} array_t;

typedef struct s_vector {
	array_t array;
	u64 size;
	u64 capacity;
	u64 type_size;
} vector_t;

static inline void
copy_array(const void *src, void *dst, u64 n) {
	for (;n;n--) {
		*((char*)dst + n) = *((char*)src + n);
	}
}

static inline void
expand_vector(vector_t *vector, void *(*alloc)(u64), void(*unalloc)(void *)) {
	void *span = 0x00;
	
	span = allocat(vector->capacity * 2);
	if (!span) {
		return;
	}
	copy_array(vector->array.ptr, span, vector->size);
	unallocat(vector->array.ptr);
	vector->array.ptr = span;
}

#endif

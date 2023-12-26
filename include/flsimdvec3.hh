#ifndef FLSIMDVEC3_HH
# define FLSIMDVEC3_HH

#include <xmmintrin.h>
#include "fldata.hh"

namespace fl {

typedef union vec3_mm_s {
	vec3 vec;
	__m128 mm_data;
} vec3_mm_t;

static inline vec3_mm_t
vec3_mm_add(const vec3_mm_t v1, const vec3_mm_t v2) {
	return ((vec3_mm_t){.mm_data = _mm_add_ps(v1.mm_data, v2.mm_data)});
}

static inline vec3_mm_t
vec3_mm_sub(const vec3_mm_t v1, const vec3_mm_t v2) {
	return ((vec3_mm_t){.mm_data = _mm_sub_ps(v1.mm_data, v2.mm_data)});
}

static inline vec3_mm_t
vec3_mm_mul(const vec3_mm_t v1, const vec3_mm_t v2) {
	return ((vec3_mm_t){.mm_data = _mm_mul_ps(v1.mm_data, v2.mm_data)});
}

static inline vec3_mm_t
vec3_mm_div(const vec3_mm_t v1, const vec3_mm_t v2) {
	return ((vec3_mm_t){.mm_data =_mm_div_ps(v1.mm_data, v2.mm_data)});
}

};

#endif

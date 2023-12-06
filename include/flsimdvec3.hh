// need to add this to compile -msse3 -O3 -Wall -lrt

#include <xmmintrin.h>
#include "fldata.hh"

namespace fl {

typedef union vec3_mm_s {
	__m128i mm_data;
	vec3 vec3;
} vec3_mm_t;

inline vec3
vec3_mm_add(vec3_mm_t v1, vec3_mm_t v2) {
	vec3_mm_t ret = {0};
	ret.mm_data = _mm_add_ss(v1.mm_data, v2.mm_data);
	return (ret.vec3);
}

inline vec3
vec3_mm_sub(vec3_mm_t v1, vec3_mm_t v2) {
	vec3_mm_t ret = {0};
	ret.mm_data = _mm_sub_ss(v1.mm_data, v2.mm_data);
	return (ret.vec3);
}

inline vec3
vec3_mm_mul(vec3_mm_t v1, vec3_mm_t v2) {
	vec3_mm_t ret = {0};
	ret.mm_data = _mm_mul_ss(v1.mm_data, v2.mm_data);
	return (ret.vec3);
}

inline vec3
vec3_mm_div(vec3_mm_t v1, vec3_mm_t v2) {
	vec3_mm_t ret = {0};
	ret.mm_data = _mm_div_ss(v1.mm_data, v2.mm_data);
	return (ret.vec3);
}

};
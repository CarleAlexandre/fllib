#ifndef FLDATA_HH
# define FLDATA_HH

#include "fltype.h"

namespace fl {

typedef struct vec2 {
	f32 x, y;
} vec2;

typedef struct vec3{
	f32 x, y, z;
} vec3;

typedef struct mat4 {
	f32 m0, m4, m8, m12;
	f32 m1, m5, m9, m13;
	f32 m2, m6, m10, m14;
	f32 m3, m7, m11, m15;
} mat4;

};

#endif

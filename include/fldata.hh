#ifndef FLDATA_HH
# define FLDATA_HH

namespace fl {

typedef struct vec2 {
	float x, y;
} vec2;

typedef struct vec3{
	float x, y, z;
} vec3;

typedef struct mat4 {
	float m0, m4, m8, m12;
	float m1, m5, m9, m13;
	float m2, m6, m10, m14;
	float m3, m7, m11, m15;
} mat4;

};

#endif

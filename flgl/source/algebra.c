#include "../Include/flgl.h"
#include <math.h>
#include <xmmintrin.h>

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

static inline float
rsqrt(float num) {
	long i;
	float x2, y;
	const float threehalfs = 1.5f;

	x2 = num * 0.5f;
	y = num;
	i = *(long *) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *) &i;
	y = y * (threehalfs - (x2 * y * y));

	return y;
}

// vec2

float distance2(vec2 v1, vec2 v2) {
    return (pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

// vec3

vec3 vec3add(const vec3 v1, const vec3 v2) {
	return(vec3_mm_add((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

vec3 vec3sub(const vec3 v1, const vec3 v2) {
	return(vec3_mm_sub((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

vec3 vec3mul(const vec3 v1, const vec3 v2) {
	return(vec3_mm_mul((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

vec3 vec3addValue(const vec3 v, const float add) {
	return(vec3_mm_add((vec3_mm_t){.vec = v}, (vec3_mm_t){.vec = {add, add, add}}).vec);
}

vec3 vec3subValue(const vec3 v, const float sub) {
    return(vec3sub(v, (vec3){sub, sub, sub}));
}

vec3 vec3mulValue(const vec3 v, float f) {
    return (vec3mul(v, (vec3){f, f, f}));
}

vec3 vec3scale(const vec3 v, const float scalar) {
	return(vec3_mm_mul((vec3_mm_t){.vec = v}, (vec3_mm_t){.vec = {scalar, scalar, scalar}}).vec);
}

vec3 vec3cross(const vec3 v1, const vec3 v2) {
	return((vec3){v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x});
}

float vec3dot(const vec3 v1, const vec3 v2) {
	const vec3 span = vec3_mm_mul((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec;
    return(span.x + span.y + span.z);
}

float vec3len(const vec3 v) {
	return (sqrtf(vec3dot(v, v)));
}

float vec3angle(const vec3 v1, const vec3 v2) {
    return (atan2f(vec3len(vec3cross(v1, v2)), vec3dot(v1, v2)));
}

vec3 vec3neg(const vec3 v) {
    return((vec3){-v.x, -v.y, -v.z});
}

vec3 vec3div(const vec3 v1, const vec3 v2) {
    return(vec3_mm_div((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

vec3 vec3divValue(const vec3 v, float f) {
    if (f != 0.0f) {
        return (vec3div(v, (vec3){f, f, f}));
    } else {
		return (v);
    }
}

float distance3(const vec3 v1, const vec3 v2) {
	const vec3 tmp = vec3sub(v1, v2);
    return(vec3dot(tmp, tmp));
}

vec3 vec3perpendicular(const vec3 v) {
    float min = fabs(v.x);
    vec3 cardinalAxis = (vec3){1.0f, 0.0f, 0.0f};
    if (fabsf(v.y) < min) {
        min = fabs(v.y);
        cardinalAxis = (vec3){0.0f, 1.0f, 0.0f};
    }
    if (fabsf(v.z) < min) {
        cardinalAxis = (vec3){0.0f, 0.0f, 1.0f};
    }
    return ((vec3){v.y*cardinalAxis.z - v.z*cardinalAxis.y, v.z*cardinalAxis.x - v.x*cardinalAxis.z, v.x*cardinalAxis.y - v.y*cardinalAxis.x});
}

vec3 vec3norm(const vec3 v) {
    float length = vec3len(v);
    if (length != 0.0f) {
        float inv_length = 1.0f/length;
    	return((vec3){v.x * inv_length, v.y * inv_length, v.z * inv_length});
    }
	return (v);
}

vec3 rotateYaw(const vec3 poi32, const vec3 center, float angle_rad) {
    float cosTheta = cos(angle_rad);
    float si32heta = sin(angle_rad);
    float rotatedX = center.x + (poi32.x - center.x) * cosTheta - (poi32.z - center.z) * si32heta;
    float rotatedZ = center.z + (poi32.x - center.x) * si32heta + (poi32.z - center.z) * cosTheta;
    return ((vec3){rotatedX, poi32.y, rotatedZ});
}

vec3 rotatePitch(const vec3 poi32, const vec3 center, float angle_rad) {
    float cosTheta = cos(angle_rad);
    float si32heta = sin(angle_rad);
    float rotatedY = center.y + (poi32.y - center.y) * cosTheta - (poi32.z - center.z) * si32heta;
    float rotatedZ = center.z + (poi32.y - center.y) * si32heta + (poi32.z - center.z) * cosTheta;
    return ((vec3){poi32.x, rotatedY, rotatedZ});
}

/*
	Travel a distance to your objectiv coordinate depending of the delta time of last frame and player velocity
*/
void travelTo(vec2 *current, const vec2 target, const float velocity, const float delta_time) {
	vec2 direction = { target.x - current->x, target.y - current->y };
    float distance_to_target = distance2(*current, target);
    float move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
		float tmp = rsqrt(distance_to_target);
        direction.x *= tmp;
        direction.y *= tmp;
        direction.x *= move_distance;
        direction.y *= move_distance;
        current->x += direction.x;
        current->y += direction.y;
    } else {
        *current = target;
    }
}

void travel3d(vec3 *current, const vec3 target, const float velocity, const float delta_time) {
    struct vec3 direction = { target.x - current->x, target.y - current->y, target.z - current->z };
    float distance_to_target = distance3(*current, target);
    float move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
		float tmp = rsqrt(distance_to_target);
        direction.x *= tmp;
        direction.y *= tmp;
		direction.z *= tmp;
        direction.x *= move_distance;
        direction.y *= move_distance;
		direction.z *= move_distance;
        current->x += direction.x;
        current->y += direction.y;
		current->z += direction.z;
    } else {
        *current = target;
    }
}

vec2 screenToWorld2D(const vec2 screen_pos, const vec2 camera_target, const int screen_width, const int screen_height, const float zoom) {
	vec2 world_pos;
	world_pos.x = (screen_pos.x - (float)screen_width / 2) / zoom + camera_target.x;
	world_pos.y = (screen_pos.y - (float)screen_height / 2) / zoom + camera_target.y;
	return (world_pos);
}

vec2 worldToScreen2D(const vec2 world_pos, const vec2 camera_target, const int screen_width, const int screen_height, const float zoom) {
	vec2 screen_pos;
	screen_pos.x = (world_pos.x - camera_target.x) * zoom + (float)screen_width / 2;
	screen_pos.y = (world_pos.y - camera_target.y) * zoom + (float)screen_height / 2;
	return (screen_pos);
}

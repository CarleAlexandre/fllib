#ifndef FLLINEAR_HH
# define FLLINEAR_HH

# include "fldata.hh"
# include "flsimdvec3.hh"
# include "flmath.hh"
# include <math.h>

namespace fl {

//vec2

static inline f32
distance2(vec2 v1, vec2 v2) {
    return (pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

//vec3

static inline vec3
vec3add(const vec3 v1, const vec3 v2) {
	return(vec3_mm_add((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

static inline vec3
vec3sub(const vec3 v1, const vec3 v2) {
	return(vec3_mm_sub((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

static inline vec3
vec3mul(const vec3 v1, const vec3 v2) {
	return(vec3_mm_mul((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

static inline vec3
vec3addValue(const vec3 v, const f32 add) {
	return(vec3_mm_add((vec3_mm_t){.vec = v}, (vec3_mm_t){.vec = {add, add, add}}).vec);
}

static inline vec3
vec3subValue(const vec3 v, const f32 sub) {
    return(vec3sub(v, {sub, sub, sub}));
}

static inline vec3
vec3mulValue(const vec3 v, f32 f) {
    return (vec3mul(v, (vec3){f, f, f}));
}

static inline vec3
vec3scale(const vec3 v, const f32 scalar) {
	return(vec3_mm_mul((vec3_mm_t){.vec = v}, (vec3_mm_t){.vec = {scalar, scalar, scalar}}).vec);
}

static inline vec3
vec3cross(const vec3 v1, const vec3 v2) {
	return((vec3){v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x});
}

static inline f32
vec3dot(const vec3 v1, const vec3 v2) {
	const vec3 span = vec3_mm_mul((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec;
    return(span.x + span.y + span.z);
}

static inline f32
vec3len(const vec3 v) {
	return (sqrtf(vec3dot(v, v)));
}

static inline f32
vec3angle(const vec3 v1, const vec3 v2) {
    return (atan2f(vec3len(vec3cross(v1, v2)), vec3dot(v1, v2)));
}

static inline vec3
vec3neg(const vec3 v) {
    return((vec3){-v.x, -v.y, -v.z});
}

static inline vec3
vec3div(const vec3 v1, const vec3 v2) {
    return(vec3_mm_div((vec3_mm_t){.vec = v1}, (vec3_mm_t){.vec = v2}).vec);
}

static inline vec3
vec3divValue(const vec3 v, f32 f) {
    if (f != 0.0f) {
        return (vec3div(v, {f, f, f}));
    } else {
		return (v);
    }
}

static inline f32
distance3(const vec3 v1, const vec3 v2) {
	const vec3 tmp = vec3sub(v1, v2);
    return(vec3dot(tmp, tmp));
}

static inline vec3
vec3perpendicular(const vec3 v) {
    f32 min = fabs(v.x);
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

static inline vec3
vec3norm(const vec3 v) {
    f32 length = vec3len(v);
    if (length != 0.0f) {
        f32 inv_length = 1.0f/length;
    	return((vec3){v.x * inv_length, v.y * inv_length, v.z * inv_length});
    }
	return (v);
}

static inline vec3
rotateYaw(const vec3 poi32, const vec3 center, f32 angle_rad) {
    f32 cosTheta = cos(angle_rad);
    f32 si32heta = sin(angle_rad);
    f32 rotatedX = center.x + (poi32.x - center.x) * cosTheta - (poi32.z - center.z) * si32heta;
    f32 rotatedZ = center.z + (poi32.x - center.x) * si32heta + (poi32.z - center.z) * cosTheta;
    return {rotatedX, poi32.y, rotatedZ};
}

static inline vec3
rotatePitch(const vec3 poi32, const vec3 center, f32 angle_rad) {
    f32 cosTheta = cos(angle_rad);
    f32 si32heta = sin(angle_rad);
    f32 rotatedY = center.y + (poi32.y - center.y) * cosTheta - (poi32.z - center.z) * si32heta;
    f32 rotatedZ = center.z + (poi32.y - center.y) * si32heta + (poi32.z - center.z) * cosTheta;
    return {poi32.x, rotatedY, rotatedZ};
}

/*
	Travel a distance to your objectiv coordinate depending of the delta time of last frame and player velocity
*/
static inline void
travelTo(vec2 *current, const vec2 target, const f32 velocity, const f32 delta_time) {
	vec2 direction = { target.x - current->x, target.y - current->y };
    f32 distance_to_target = distance2(*current, target);
    f32 move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
		f32 tmp = rsqrt(distance_to_target);
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

static inline void
travel3d(vec3 *current, const vec3 target, const f32 velocity, const f32 delta_time) {
    struct vec3 direction = { target.x - current->x, target.y - current->y, target.z - current->z };
    f32 distance_to_target = distance3(*current, target);
    f32 move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
		f32 tmp = rsqrt(distance_to_target);
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

static inline vec2
screenToWorld2D(const vec2 screen_pos, const vec2 camera_target, const i32 screen_width, const i32 screen_height, const f32 zoom) {
	vec2 world_pos;
	world_pos.x = (screen_pos.x - (f32)screen_width / 2) / zoom + camera_target.x;
	world_pos.y = (screen_pos.y - (f32)screen_height / 2) / zoom + camera_target.y;
	return (world_pos);
}

static inline vec2
worldToScreen2D(const vec2 world_pos, const vec2 camera_target, const i32 screen_width, const i32 screen_height, const f32 zoom) {
	vec2 screen_pos;
	screen_pos.x = (world_pos.x - camera_target.x) * zoom + (f32)screen_width / 2;
	screen_pos.y = (world_pos.y - camera_target.y) * zoom + (f32)screen_height / 2;
	return (screen_pos);
}

};
# endif
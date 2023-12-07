#ifndef FLLINEAR_HH
# define FLLINEAR_HH

# include "fldata.hh"
# include "flsimdvec3.hh"
# include "flmath.h"
# include "math.h"

namespace fl {

//vec2

inline float
distance2(vec2 v1, vec2 v2) {
    return (pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

//vec3

inline vec3
vec3add(const vec3 v1, const vec3 v2) {
	return(vec3_mm_add((vec3_mm_t){.vec3 = v1}, (vec3_mm_t){.vec3 = v2}));
}

inline vec3
vec3sub(const vec3 v1, const vec3 v2) {
	return(vec3_mm_sub((vec3_mm_t){.vec3 = v1}, (vec3_mm_t){.vec3 = v2}));
}

inline vec3
vec3mul(const vec3 v1, const vec3 v2) {
	return(vec3_mm_mul((vec3_mm_t){.vec3 = v1}, (vec3_mm_t){.vec3 = v2}));
}

inline vec3
vec3addValue(const vec3 v, const float add) {
	return(vec3_mm_add((vec3_mm_t){.vec3 = v}, (vec3_mm_t){.vec3 = {add, add, add}}));
}

inline vec3
vec3subValue(const vec3 v, const float sub) {
    return(vec3sub(v, {sub, sub, sub}));
}

inline vec3
vec3mulValue(const vec3 v, float f) {
    return (vec3mul(v, (vec3){f, f, f}));
}

inline vec3
vec3scale(const vec3 v, const float scalar) {
	return(vec3_mm_mul((vec3_mm_t){.vec3 = v}, (vec3_mm_t){.vec3 = {scalar, scalar, scalar}}));
}

inline vec3
vec3cross(const vec3 v1, const vec3 v2) {
	return((vec3){v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x});
}

inline float
vec3dot(const vec3 v1, const vec3 v2) {
	const vec3 span = vec3_mm_mul((vec3_mm_t){.vec3 = v1}, (vec3_mm_t){.vec3 = v2});
    return(span.x + span.y + span.z);
}

inline float
vec3len(const vec3 v) {
	return (sqrtf(vec3dot(v, v)));
}

inline float
vec3angle(const vec3 v1, const vec3 v2) {
    return (atan2f(vec3len(vec3cross(v1, v2)), vec3dot(v1, v2)));
}

inline vec3
vec3neg(const vec3 v) {
    return((vec3){-v.x, -v.y, -v.z});
}

inline vec3
vec3div(const vec3 v1, const vec3 v2) {
    return(vec3_mm_div((vec3_mm_t){.vec3 = v1}, (vec3_mm_t){.vec3 = v2}));
}

inline vec3
vec3divValue(const vec3 v, float f) {
    if (f != 0.0f) {
        return (vec3div(v, {f, f, f}));
    } else {
		return (v);
    }
}

inline float
distance3(const vec3 v1, const vec3 v2) {
	const vec3 tmp = vec3sub(v1, v2);
    return(vec3dot(tmp, tmp));
}

inline vec3
vec3perpendicular(const vec3 v) {
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

inline vec3
vec3norm(const vec3 v) {
    float length = vec3len(v);
    if (length != 0.0f) {
        float inv_length = 1.0f/length;
    	return((vec3){v.x * inv_length, v.y * inv_length, v.z * inv_length});
    }
	return (v);
}

inline vec3
rotateYaw(const vec3 point, const vec3 center, float angle_rad) {
    float cosTheta = cos(angle_rad);
    float sinTheta = sin(angle_rad);
    float rotatedX = center.x + (point.x - center.x) * cosTheta - (point.z - center.z) * sinTheta;
    float rotatedZ = center.z + (point.x - center.x) * sinTheta + (point.z - center.z) * cosTheta;
    return {rotatedX, point.y, rotatedZ};
}

inline vec3
rotatePitch(const vec3 point, const vec3 center, float angle_rad) {
    float cosTheta = cos(angle_rad);
    float sinTheta = sin(angle_rad);
    float rotatedY = center.y + (point.y - center.y) * cosTheta - (point.z - center.z) * sinTheta;
    float rotatedZ = center.z + (point.y - center.y) * sinTheta + (point.z - center.z) * cosTheta;
    return {point.x, rotatedY, rotatedZ};
}

/*
	Travel a distance to your objectiv coordinate depending of the delta time of last frame and player velocity
*/
inline void
travelTo(vec2 *current, const vec2 target, const float velocity, const float delta_time) {
	vec2 direction = { target.x - current->x, target.y - current->y };
    float distance_to_target = distance2(*current, target);
    float move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
        direction.x *= Q_rsqrt(distance_to_target);
        direction.y *= Q_rsqrt(distance_to_target);
        direction.x *= move_distance;
        direction.y *= move_distance;
        current->x += direction.x;
        current->y += direction.y;
    } else {
        *current = target;
    }
}

inline void
travel3d(vec3 *current, const vec3 target, const float velocity, const float delta_time) {
    struct vec3 direction = { target.x - current->x, target.y - current->y, target.z - current->z };
    float distance_to_target = distance3(*current, target);
    float move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
        direction.x *= Q_rsqrt(distance_to_target);
        direction.y *= Q_rsqrt(distance_to_target);
		direction.z *= Q_rsqrt(distance_to_target);
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

inline vec2
screenToWorld2D(const vec2 screen_pos, const vec2 camera_target, const int screen_width, const int screen_height, const float zoom) {
	vec2 world_pos;
	world_pos.x = (screen_pos.x - (float)screen_width / 2) / zoom + camera_target.x;
	world_pos.y = (screen_pos.y - (float)screen_height / 2) / zoom + camera_target.y;
	return (world_pos);
}

inline vec2
worldToScreen2D(const vec2 world_pos, const vec2 camera_target, const int screen_width, const int screen_height, const float zoom) {
	vec2 screen_pos;
	screen_pos.x = (world_pos.x - camera_target.x) * zoom + (float)screen_width / 2;
	screen_pos.y = (world_pos.y - camera_target.y) * zoom + (float)screen_height / 2;
	return (screen_pos);
}

};
# endif
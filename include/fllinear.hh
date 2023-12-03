#ifndef FLLINEAR_HH
# define FLLINEAR_HH

# include "fldata.hh"
# include "flmath.h"

namespace fl {

inline float
distance2(vec2 v1, vec2 v2) {
    return (pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

inline float
distance3(vec3 v1, vec3 v2) {
    return(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
}

inline vec3
vec3add(const vec3 v1, const vec3 v2) {
	return((vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

inline vec3
vec3sub(const vec3 v1, const vec3 v2) {
	return((vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

inline vec3
vec3addValue(const vec3 v, const float add) {
	return((vec3){v.x + add, v.y + add, v.z + add});
}

inline vec3
vec3subValue(const vec3 v, const float add) {
    return((vec3){v.x - add, v.y - add, v.z - add});
}

inline vec3
vec3scale(const vec3 v, const float scalar) {
	return((vec3){v.x*scalar, v.y*scalar, v.z*scalar});
}

inline vec3
vec3mul(const vec3 v1, const vec3 v2) {
	return((vec3){v1.x*v2.x, v1.y*v2.y, v1.z*v2.z});
}

inline vec3
vec3cross(const vec3 v1, const vec3 v2) {
	return((vec3){v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x});
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

inline float
vec3len(const vec3 v) {
	return (sqrtf(v.x*v.x + v.y*v.y + v.z*v.z));
}

inline float
vec3lenSqr(const vec3 v) {
    return (v.x*v.x + v.y*v.y + v.z*v.z);
}

inline float
vec3dot(const vec3 v1, const vec3 v2) {
    return(v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
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
    return((vec3){v1.x/v2.x, v1.y/v2.y, v1.z/v2.z});
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
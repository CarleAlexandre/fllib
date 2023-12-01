#ifndef FLLINEAR_HH
# define FLLINEAR_HH

# include "fldata.hh"
# include "flmath.h"

namespace fl {

inline float
distance2(vec2 a, vec2 b) {
    return (flPow(b.x - a.x, 2) + flPow(b.y - a.y, 2));
}

inline float
distance3(vec3 a, vec3 b) {
    return (flPow(b.x - a.x, 2) + flPow(b.y - a.y, 2) + flPow(b.z - a.z, 2));
}


/*
	Travel a distance to your objectiv coordinate depending of the delta time of last frame and player velocity
*/
inline vec2
travelTo(vec2 current, vec2 target, float velocity, float delta_time) {
	vec2 direction = { target.x - current.x, target.y - current.y };
    float distance_to_target = distance2(current, target);
    float move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
        direction.x *= Q_rsqrt(distance_to_target);
        direction.y *= Q_rsqrt(distance_to_target);
        direction.x *= move_distance;
        direction.y *= move_distance;
        current.x += direction.x;
        current.y += direction.y;
    } else {
        current = target;
    }
    return (current);
}

inline vec3
travel3d(vec3 current, vec3 target, float velocity, float delta_time) {
    struct vec3 direction = { target.x - current.x, target.y - current.y, target.z - current.z };
    float distance_to_target = distance3(current, target);
    float move_distance = velocity * delta_time;
    if (distance_to_target > move_distance * move_distance) {
        direction.x *= Q_rsqrt(distance_to_target);
        direction.y *= Q_rsqrt(distance_to_target);
		direction.z *= Q_rsqrt(distance_to_target);
        direction.x *= move_distance;
        direction.y *= move_distance;
		direction.z *= move_distance;
        current.x += direction.x;
        current.y += direction.y;
		current.z += direction.z;
    } else {
        current = target;
    }
    return (current);
}

inline vec2
screenToWorld2D(vec2 screen_pos, vec2 camera_target, int screen_width, int screen_height, float zoom) {
	vec2 world_pos;
	world_pos.x = (screen_pos.x - (float)screen_width / 2) / zoom + camera_target.x;
	world_pos.y = (screen_pos.y - (float)screen_height / 2) / zoom + camera_target.y;
	return (world_pos);
}

inline vec2
worldToScreen2D(vec2 world_pos, vec2 camera_target, int screen_width, int screen_height, float zoom) {
	vec2 screen_pos;
	screen_pos.x = (world_pos.x - camera_target.x) * zoom + (float)screen_width / 2;
	screen_pos.y = (world_pos.y - camera_target.y) * zoom + (float)screen_height / 2;
	return (screen_pos);
}

};
# endif
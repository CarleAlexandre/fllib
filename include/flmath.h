/*
 * =====================================================================================
 *
 *       Filename:  flmath.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/12/2023 05:11:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fatmeat (), pathofyggdrasil@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef FLMATH_H
# define FLMATH_H

struct
Vector2 {
	float x, y;
};

struct
Vector3 {
	float x, y, z;
};

inline int
fl_gcd(int a, int b) {
	while (1) {
		if (b == 0) {
			break;
		}
		a ^= b;
		b ^= a;
		a ^= b;
		b %= a;
	}
	return (a);
}

inline float
Q_rsqrt(float num) {
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

inline float
flLerp(float a, float b, float x) {
	if (x <= 0.5f)
		return (x * (b - a) + a);
	return (b - (1.0f - x) * (b - a));
}

inline double
flPow(double number, long power) {
	double result = 1;
	while (power > 0) { 
		if (power & 1) {
			result *= (result * number);
		}
		number = (number * number);
		power >>= 1;
	}
	return (result);
}

inline float
smoothStep(float t) {
    float v1 = t * t;
    float v2 = 1.0f - (1.0f - t) * (1.0f - t);
    return (flLerp(v1, v2, t));
}

inline float
flDistance2(Vector2 a, Vector2 b) {
    return (flPow(b.x - a.x, 2) + flPow(b.y - a.y, 2));
}

inline float
flDistance3(Vector3 a, Vector3 b) {
    return (flPow(b.x - a.x, 2) + flPow(b.y - a.y, 2) + flPow(b.z - a.z, 2));
}


/*
	Travel a distance to your objectiv coordinate depending of the delta time of last frame and player velocity
*/
inline Vector2
flTravelTo(Vector2 current, Vector2 target, float velocity, float delta_time) {
	Vector2 direction = { target.x - current.x, target.y - current.y };
    float distance_to_target = flDistance2(current, target);
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

inline Vector3
flTravel3d(struct Vector3 current, struct Vector3 target, float velocity, float delta_time) {
    struct Vector3 direction = { target.x - current.x, target.y - current.y, target.z - current.z };
    float distance_to_target = flDistance3(current, target);
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

inline Vector2
screenToWorld2D(Vector2 screen_pos, Vector2 camera_target, int s_width, int s_height, float zoom) {
	Vector2 world_pos;
	world_pos.x = (screen_pos.x - (float)s_width / 2) / zoom + camera_target.x;
	world_pos.y = (screen_pos.y - (float)s_height / 2) / zoom + camera_target.y;
	return (world_pos);
}

inline Vector2
worldToScreen2D(Vector2 world_pos, Vector2 camera_target, int s_width, int s_height, float zoom) {
	Vector2 screen_pos;
	screen_pos.x = (world_pos.x - camera_target.x) * zoom + (float)s_width / 2;
	screen_pos.y = (world_pos.y - camera_target.y) * zoom + (float)s_height / 2;
	return (screen_pos);
}

#endif

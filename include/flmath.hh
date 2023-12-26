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

#include "fltype.h"

namespace fl {

static inline i32
gcd(i32 a, i32 b) {
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

static inline f32
rsqrt(f32 num) {
	long i;
	f32 x2, y;
	const f32 threehalfs = 1.5f;

	x2 = num * 0.5f;
	y = num;
	i = *(long *) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(f32 *) &i;
	y = y * (threehalfs - (x2 * y * y));

	return y;
}

static inline f32
lerp(f32 a, f32 b, f32 x) {
	if (x <= 0.5f)
		return (x * (b - a) + a);
	return (b - (1.0f - x) * (b - a));
}

static inline f64
pow(f64 number, long power) {
	f64 result = 1;
	while (power > 0) { 
		if (power & 1) {
			result *= (result * number);
		}
		number = (number * number);
		power >>= 1;
	}
	return (result);
}

static inline f32
smoothStep(f32 t) {
    f32 v1 = t * t;
    f32 v2 = 1.0f - (1.0f - t) * (1.0f - t);
    return (lerp(v1, v2, t));
}

};

#endif

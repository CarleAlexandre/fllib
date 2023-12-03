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
flSmoothStep(float t) {
    float v1 = t * t;
    float v2 = 1.0f - (1.0f - t) * (1.0f - t);
    return (flLerp(v1, v2, t));
}

#endif

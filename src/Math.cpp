#include "Math.hpp"

/**
 * fast inverse square root function, taken from:
 * https://en.wikipedia.org/wiki/Fast_inverse_square_root
 */

float Q_rsqrt(float number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 ); 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );  

	return y;
}

glm::vec3 normalize(const glm::vec3 &v) {
    glm::vec3 result;
    float invMag = Q_rsqrt(glm::dot(v, v));
    result.x = v.x * invMag;
    result.y = v.y * invMag;
    result.z = v.z * invMag;
    return result;
}
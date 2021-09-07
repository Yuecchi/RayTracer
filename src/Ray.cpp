#include "Ray.hpp"

#include <glm/geometric.hpp>

float Q_rsqrt( float number )
{
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

Ray::Ray() = default;

void Ray::setOrigin(const glm::vec3 &v) {
    m_origin = v;
}

void Ray::setDirection(const glm::vec3 &v) {
    float invMag = Q_rsqrt(glm::dot(v, v));
    m_direction.x = v.x * invMag;
    m_direction.y = v.y * invMag;
    m_direction.z = v.z * invMag;
}

glm::vec3 &Ray::origin() {
    return m_origin;
}

glm::vec3 &Ray::direction() {
    return m_direction;
}

Ray::~Ray() = default;
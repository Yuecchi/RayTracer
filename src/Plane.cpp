#include <cmath>

#include <glm/geometric.hpp>

#include "Plane.hpp"

Plane::Plane(glm::vec3 normal, float distance, glm::vec3 color) {
	m_normal = normal;
    glm::normalize(m_normal);
    m_distance = distance;
    m_origin = m_normal * m_distance;
	m_color = color;
}

float Plane::rayIntersect(Ray *ray) {
	float denom = glm::dot(ray->direction(), m_normal);
	if (fabs(denom) > 1e-6) {
		glm::vec3 w = m_origin - ray->origin();
		float numer = glm::dot(w, m_normal);
		float t = numer / denom;
		if (t >= 1e-6) {
			return t;
		}
		else return INFINITY;
	}
	return INFINITY;
}

glm::vec3 Plane::normal(const glm::vec3 &v) {
	return m_normal;
}

glm::vec3 &Plane::color() {
	return m_color;
}

Plane::~Plane() = default;
#include <cmath>

#include "Plane.hpp"
#include "Math.hpp"

Plane::Plane(glm::vec3 normal, float distance, glm::vec3 color) {
	m_normal = normalize(normal);
    m_distance = distance;
    m_origin = m_normal * m_distance;
	m_color = color;
}

RayIntersectData Plane::rayIntersect(Ray ray) {
	RayIntersectData result = {
		nullptr, INFINITY
	};
	float denom = glm::dot(ray.direction(), m_normal);
	if (fabs(denom) > 1e-6) {
		glm::vec3 w = m_origin - ray.origin();
		float numer = glm::dot(w, m_normal);
		float t = numer / denom;
		if (t >= 1e-6) {
			result.distance = t;
			result.sceneObject = this;
			return result;
		}
		else return result;
	}
	return result;
}

glm::vec3 Plane::normal(const glm::vec3 &v) {
	return m_normal;
}

glm::vec3 &Plane::color() {
	return m_color;
}

Plane::~Plane() = default;
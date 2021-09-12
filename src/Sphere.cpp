#include <cmath>

#include "Sphere.hpp"
#include "Math.hpp"

Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 color) {
    m_position = position;
    m_radius = radius;
	m_color = color;
}

RayIntersectData Sphere::rayIntersect(Ray ray) {
	RayIntersectData result = {
		nullptr, INFINITY
	};
	glm::vec3 w = ray.origin() - m_position;

	float a = glm::dot(ray.direction(), ray.direction());
	float b = glm::dot(ray.direction(), w);
	float c = glm::dot(w, w) - (m_radius * m_radius);

	float discr = (b * b) - (a * c);
	if (discr < 0) return result; //no intersection

	float t = (-b - sqrt(discr)) / a;
	if (t > 0.0f) {
		result.distance = t;
		result.sceneObject = this;
		return result;
	}
	else return result;
}

glm::vec3 Sphere::normal(const glm::vec3 &v) {
	return normalize(v - m_position);
}

glm::vec3 &Sphere::color() {
	return m_color;
}

Sphere::~Sphere() = default;
#include <cmath>

#include <glm/gtx/rotate_vector.hpp>

#include "Plane.hpp"
#include "Math.hpp"

Plane::Plane(glm::vec3 normal, float distance, Material material) {
	m_normal = normalize(normal);
    m_distance = distance;
    m_origin = m_normal * m_distance;
	m_material = material;

	m_u = glm::rotateX(m_normal, PI / 2.0f);
	m_v = glm::rotateY(m_u, PI / 2.0f);
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

void Plane::color(glm::vec3 &hitpos, glm::vec3 *result) {
	static const glm::vec3 origin = glm::vec3(0.0f);

	// project the hitpos onto vectors u and v
	glm::vec3 p_proj_u = m_u * glm::dot(hitpos, m_u);
	glm::vec3 p_proj_v = m_v * glm::dot(hitpos, m_v);

	// calulate the distance between the origin and the projections
	glm::vec3 ou = p_proj_u - origin;
	glm::vec3 ov = p_proj_v - origin;
	glm::vec2 texCoords = {
		sqrt(glm::dot(ou, ou)),	
		sqrt(glm::dot(ov, ov))
	};

	// send the resulting values to the texture to recieve a color
	m_material.texture->color(texCoords, result);
}


glm::vec3 Plane::normal(const glm::vec3 &v) {
	return m_normal;
}

Plane::~Plane() = default;
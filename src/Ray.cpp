#include <glm/geometric.hpp>

#include "Ray.hpp"
#include "Math.hpp"

Ray::Ray() = default;

void Ray::setOrigin(const glm::vec3 &v) {
    m_origin = v;
}

void Ray::setDirection(const glm::vec3 &v) {   
    m_direction = normalize(v);
}

glm::vec3 &Ray::origin() {
    return m_origin;
}

glm::vec3 &Ray::direction() {
    return m_direction;
}

Ray::~Ray() = default;
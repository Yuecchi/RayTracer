#include "Ray.hpp"

#include <glm/geometric.hpp>

Ray::Ray() = default;

void Ray::setOrigin(glm::vec3 v) {
    m_origin.x = v.x;
    m_origin.y = v.y;
    m_origin.z = v.z;    
}

void Ray::setDirection(float x, float y, float z) {
    m_direction.x = x;
    m_direction.y = y;
    m_direction.z = z;
    normalize();
}

void Ray::setDirection(glm::vec3 v) {
    m_direction.x = v.x;
    m_direction.y = v.y;
    m_direction.z = v.z;
    normalize();
}

void Ray::normalize() {
    float length = glm::length(m_direction);
    m_direction /= length;
}

glm::vec3 &Ray::origin() {
    return m_origin;
}

glm::vec3 &Ray::direction() {
    return m_direction;
}

Ray::~Ray() = default;
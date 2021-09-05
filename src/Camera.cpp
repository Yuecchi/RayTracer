#include <glm/gtx/rotate_vector.hpp>

#include "Camera.hpp"

Camera::Camera() = default;

glm::vec3 &Camera::position() {
    return m_position;
}

glm::vec3 &Camera::direction() {
    return m_direction;
}

glm::vec3 &Camera::up() {
    return m_up;
}

glm::vec3 &Camera::right() {
    return m_right;
}

void Camera::setPosition(glm::vec3 position) {
    m_position = position;
}

void Camera::move(glm::vec3 v) {
    m_position += v;
}

void Camera::rotate(float theta) {
    m_direction = glm::rotate(m_direction, -theta, m_up);
    m_right = glm::rotate(m_right, -theta, m_up);
}

Camera::~Camera() = default;
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

Camera::~Camera() = default;
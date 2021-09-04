#include "Light.hpp"

Light::Light(glm::vec3 position, float intensity) {
    m_position = position;
    m_intensity = intensity;
} 

glm::vec3 &Light::position() {
    return m_position;
}

float Light::intensity() {
    return m_intensity;
}

Light::~Light() = default;
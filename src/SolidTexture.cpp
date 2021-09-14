#include "SolidTexture.hpp"

SolidTexture::SolidTexture(glm::vec3 color) {
    m_color = color;
}

void SolidTexture::color(glm::vec2 &texCoords, glm::vec3 *result) {
    *result = m_color;
}

SolidTexture::~SolidTexture() = default;
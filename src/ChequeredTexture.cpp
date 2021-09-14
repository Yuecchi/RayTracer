#include <cmath>

#include "ChequeredTexture.hpp"

ChequeredTexture::ChequeredTexture(int scale) {
    m_scale = scale;
}
        
void ChequeredTexture::color(glm::vec2 &texCoords, glm::vec3 *result) {
    int ud = round(texCoords.x / m_scale);
    int vd = round(texCoords.y / m_scale);

    if (!(ud % 2) && !(vd % 2) || (ud % 2) && (vd % 2)) *result = glm::vec3(0.0f);
	else *result = glm::vec3(1.0f);
}

ChequeredTexture::~ChequeredTexture() = default;
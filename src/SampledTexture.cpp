#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "SampledTexture.hpp"

SampledTexture::SampledTexture(const char *filepath) {
    float *data = stbi_loadf(filepath, &m_width, &m_height, &m_bpp, 0);
    m_pixels = new glm::vec3*[m_width];
    for (int x = 0; x < m_width; x += 1) {
        m_pixels[x] = new glm::vec3[m_height];
        for (int y = 0; y < m_height; y += 1) {
            m_pixels[x][y].r = data[(y * m_height * m_bpp) + (x * m_bpp)];
            m_pixels[x][y].g = data[(y * m_height * m_bpp) + (x * m_bpp) + 1];;
            m_pixels[x][y].b = data[(y * m_height * m_bpp) + (x * m_bpp) + 2];;
        }
    }
    stbi_image_free(data);
}

void SampledTexture::color(glm::vec2 &texCoords, glm::vec3 *result) {
    int scalex = m_width / (m_width / 32);
    int scaley = m_height/ (m_height / 32);
    int x = ((int)round(texCoords.x * scalex) % m_width);
    int y = ((int)round(texCoords.y * scaley) % m_height);
    *result = m_pixels[x][y];
}

SampledTexture::~SampledTexture() {
    for (int x = 0; x < m_width; x += 1) {
        delete m_pixels[x];
    }
    delete m_pixels;
}
#pragma once

#include "Texture.hpp"

class SampledTexture : public Texture {
    
    private:

        glm::vec3 **m_pixels;

        int m_width;
        int m_height;
        int m_bpp;

    public:

        SampledTexture(const char *filepath);

        void color(glm::vec2 &texCoords, glm::vec3 *result);

        ~SampledTexture();

};
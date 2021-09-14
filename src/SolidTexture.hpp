#pragma once

#include "Texture.hpp"

class SolidTexture : public Texture {

    private:

        glm::vec3 m_color;

    public:

        SolidTexture(glm::vec3 color);

        void color(glm::vec2 &texCoords, glm::vec3 *result);

        ~SolidTexture();

};
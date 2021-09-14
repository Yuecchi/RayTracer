#pragma once

#include "Texture.hpp"

class ProceduralTexture : public Texture {
    
    protected:

        int m_scale;

    public:

        ProceduralTexture();

        virtual void color(glm::vec2 &texCoords, glm::vec3 *result) = 0;

        virtual ~ProceduralTexture();

};
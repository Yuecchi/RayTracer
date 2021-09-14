#pragma once

#include "ProceduralTexture.hpp"

class ChequeredTexture : public ProceduralTexture {

    public:

        ChequeredTexture(int scale);
        
        void color(glm::vec2 &texCoords, glm::vec3 *result);

        ~ChequeredTexture();

};
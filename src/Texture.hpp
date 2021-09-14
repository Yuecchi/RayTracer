#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Texture {

    public:

        Texture();

        Texture(int width, int height, int bpp);

        virtual void color(glm::vec2 &texCoords, glm::vec3 *result) = 0;

        virtual ~Texture();

};
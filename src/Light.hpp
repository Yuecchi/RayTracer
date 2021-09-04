#pragma once

#include <glm/vec3.hpp>

class Light {

    private:

        glm::vec3 m_position;
        float m_intensity;

    public:

        Light(glm::vec3 position, float intensity);

        glm::vec3 &position();

        float intensity();

        ~Light();

};
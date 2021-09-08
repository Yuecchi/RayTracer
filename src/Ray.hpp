#pragma once

#include <glm/vec3.hpp>

class Ray {

    private:

        glm::vec3 m_origin = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, 0.0f);

    public:

        Ray();

        void setOrigin(const glm::vec3 &v);

        void setDirection(const glm::vec3 &v);

        glm::vec3 &origin();

        glm::vec3 &direction();

        ~Ray();

};
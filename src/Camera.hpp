#pragma once

#include <glm/vec3.hpp>

class Camera {

    private:

        glm::vec3 m_position  = glm::vec3( 0.0f,  0.0f,  0.0f);
        glm::vec3 m_direction = glm::vec3( 0.0f,  0.0f, -1.0f);
        glm::vec3 m_up        = glm::vec3( 0.0f,  1.0f,  0.0f);
        glm::vec3 m_right     = glm::vec3( 1.0f,  0.0f,  0.0f);

    public:

        Camera();

        glm::vec3 &position();

        glm::vec3 &direction();

        glm::vec3 &up();

        glm::vec3 &right();

        void setPosition(glm::vec3 position);

        void rotate(float theta);

        void move(glm::vec3 v);

        ~Camera();

};
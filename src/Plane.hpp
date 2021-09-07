#pragma once

#include "glm/vec3.hpp"

#include "Primitive.hpp"

class Plane : public Primitive {

    private:

        glm::vec3 m_normal;
        glm::vec3 m_origin;
        float m_distance;

    public:

        Plane(glm::vec3 normal, float distance, glm::vec3 color);

        float rayIntersect(Ray ray);

        glm::vec3 normal(const glm::vec3 &v);

        glm::vec3 &color();

        ~Plane();

};
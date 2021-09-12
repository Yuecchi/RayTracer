#pragma once

#include "Primitive.hpp"

class Triangle : public Primitive {
    private:

        glm::vec3 m_p1, m_p2, m_p3;
        glm::vec3 m_normal;

        void computeNormal();

    public:
        
        Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color);

        float rayIntersect(Ray ray);

        glm::vec3 normal(const glm::vec3 &v);

        glm::vec3 &color();

        ~Triangle();
};
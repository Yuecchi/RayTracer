#pragma once

#include "Primitive.hpp"

class Sphere : public Primitive {

    private:

        float m_radius;

        glm::vec3 m_position;

    public:

        Sphere(glm::vec3 position, float radius, glm::vec3 color);

        RayIntersectData rayIntersect(Ray ray);

        glm::vec3 normal(const glm::vec3 &v);

        glm::vec3 &color();

        ~Sphere();

};
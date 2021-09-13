#pragma once

#include "Primitive.hpp"

class Plane : public Primitive {

    private:

        glm::vec3 m_normal;
        glm::vec3 m_origin;
        float m_distance;

    public:

        Plane(glm::vec3 normal, float distance, Material material);

        RayIntersectData rayIntersect(Ray ray);

        glm::vec3 normal(const glm::vec3 &v);

        ~Plane();

};
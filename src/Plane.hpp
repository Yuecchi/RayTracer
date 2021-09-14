#pragma once

#include "Primitive.hpp"

class Plane : public Primitive {

    private:

        glm::vec3 m_normal;
        glm::vec3 m_origin;
        float m_distance;

        glm::vec3 m_u;
        glm::vec3 m_v;

    public:

        Plane(glm::vec3 normal, float distance, Material material);

        RayIntersectData rayIntersect(Ray ray);

        void color(glm::vec3 &hitpos, glm::vec3 *result);

        glm::vec3 normal(const glm::vec3 &v);

        ~Plane();

};
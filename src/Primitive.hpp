#pragma once

#include "Ray.hpp"

class Primitive {

    private:

    protected: 

        glm::vec3 m_color;

    public:

        Primitive();

        virtual float rayIntersect(Ray ray) = 0;

        virtual glm::vec3 normal(const glm::vec3 &v) = 0;

        virtual glm::vec3 &color() = 0;

        virtual ~Primitive();

};
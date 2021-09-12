#pragma once

#include "SceneObject.hpp"

class Primitive : public SceneObject {

    protected: 

        glm::vec3 m_color;

    public:

        Primitive();

        virtual RayIntersectData rayIntersect(Ray ray) = 0; 

        virtual glm::vec3 normal(const glm::vec3 &v) = 0;

        virtual glm::vec3 &color() = 0;

        virtual ~Primitive();

};


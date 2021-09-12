#pragma once

#include "Ray.hpp"
#include "Primitive.hpp"

class BoundingBox {
    
    private:

        glm::vec3 m_min;
        glm::vec3 m_max;

    public:

        BoundingBox();

        void setBoundaries(const glm::vec3 &min, const glm::vec3 &max);

        bool rayIntersect(Ray &ray); 

        glm::vec3 normal(const glm::vec3 &v);

        ~BoundingBox();

};
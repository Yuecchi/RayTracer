#pragma once

#include "SceneObject.hpp"

struct Material {
    glm::vec3 color;
    float ambienceCoeff;
    float diffuseCoeff;
    float specularCoeff;
    float reflectiveCoeff;
    int shininess;
};

class Primitive : public SceneObject {

    protected: 

        Material m_material;

    public:

        Primitive();

        virtual RayIntersectData rayIntersect(Ray ray) = 0; 

        virtual glm::vec3 normal(const glm::vec3 &v) = 0;

        glm::vec3 &color();

        float ambience();

        float diffuse();

        float specular();

        float reflectivity();

        float shininess();

        virtual ~Primitive();

};


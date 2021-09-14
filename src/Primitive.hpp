#pragma once

#include "SceneObject.hpp"
#include "Texture.hpp"

struct Material {
    Texture *texture;
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

        virtual void color(glm::vec3 &hitpos, glm::vec3 *result);

        float ambience();

        float diffuse();

        float specular();

        float reflectivity();

        float shininess();

        virtual ~Primitive();

};


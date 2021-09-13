#include "Primitive.hpp" 

Primitive::Primitive() = default;

glm::vec3 &Primitive::color() {
    return m_material.color;
}

float Primitive::ambience() {
    return m_material.ambienceCoeff;
}

float Primitive::diffuse() {
    return m_material.diffuseCoeff;
}

float Primitive::specular() {
    return m_material.specularCoeff;
}

float Primitive::reflectivity() {
    return m_material.reflectiveCoeff;
}
        
float Primitive::shininess() {
    return m_material.shininess;
}

Primitive::~Primitive() = default;  
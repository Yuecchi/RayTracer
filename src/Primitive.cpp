#include "Primitive.hpp" 

Primitive::Primitive() = default;

void Primitive::color(glm::vec3 &hitpos, glm::vec3 *result) {
    static glm::vec2 v = glm::vec2(0.0f);
    m_material.texture->color(v, result);
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
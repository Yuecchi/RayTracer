#pragma once

#include <vector>
#include <string>

#include "SceneObject.hpp"
#include "Triangle.hpp"

class Mesh : public SceneObject {

    private:

        std::vector<Triangle*> m_polys; 

    public:

        Mesh(const std::string &filepath);

        RayIntersectData rayIntersect(Ray ray);

        std::vector<Triangle*> polys();

        ~Mesh();

};
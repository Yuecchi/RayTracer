#pragma once

#include <vector>
#include <string>

#include "Triangle.hpp"

class Mesh {

    private:

        std::vector<Triangle*> m_polys; 

    public:

        Mesh(const std::string &filepath);

        std::vector<Triangle*> polys();

        ~Mesh();

};
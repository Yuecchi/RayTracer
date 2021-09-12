#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#include <glm/vec3.hpp>

#include "Mesh.hpp"

const int BUFFER_SIZE = 128;

Mesh::Mesh(const std::string &filepath) {   
    std::ifstream meshFile(filepath);
    std::vector<glm::vec3> vertices;
    char buffer[BUFFER_SIZE];
    int index[3];
    float x, y, z;

    if (!meshFile.is_open()) {
        std::cout << "Failed to open file " << filepath << "\n";
    } else {
        while(!meshFile.eof()) {
            meshFile.getline(buffer, BUFFER_SIZE);
            std::stringstream ss;
            ss << buffer;
            
            char junk;
            if (buffer[0] == 'v') {
                glm::vec3 vertex;
                ss >> junk >> vertex.x >> vertex.y >> vertex.z;
                vertices.push_back(vertex);
            } else if (buffer[0] == 'f') {
                ss >> junk >> index[0] >> index[1] >> index[2];
                m_polys.push_back(new Triangle(vertices[index[0] - 1], vertices[index[1] - 1], vertices[index[2] - 1], glm::vec3(0.5f)));
            }
        }
    }
}

RayIntersectData Mesh::rayIntersect(Ray ray) {
    RayIntersectData result = {
        nullptr,
        INFINITY
    };

    RayIntersectData intermediate;
    for (Triangle *t : m_polys) {
        intermediate = t->rayIntersect(ray);
        if (result.distance > intermediate.distance) {
            result.distance = intermediate.distance;
            result.sceneObject = intermediate.sceneObject;
        }
    }

    return result;
}

std::vector<Triangle*> Mesh::polys() {
    return m_polys;
}

Mesh::~Mesh() {
    for (Triangle *t : m_polys) {
        delete t;
    }
}
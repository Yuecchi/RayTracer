#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iostream>

#include <glm/vec3.hpp>

#include "Mesh.hpp"
#include "SolidTexture.hpp"

const int BUFFER_SIZE = 128;

void Mesh::computeBoundingBox() {
    glm::vec3 min = glm::vec3(INFINITY);
    glm::vec3 max = glm::vec3(-INFINITY);
    for (Triangle *t : m_polys) {
        // find the minimum x, y and z values in the mesh
        float minx = std::min(t->p1().x, std::min(t->p2().x, t->p3().x));
        float miny = std::min(t->p1().y, std::min(t->p2().y, t->p3().y));
        float minz = std::min(t->p1().z, std::min(t->p2().z, t->p3().z));
        min.x = min.x > minx ? minx : min.x;
        min.y = min.y > miny ? miny : min.y;
        min.z = min.z > minz ? minz : min.z;

        // find the maximum x, y and z values in the mesh
        float maxx = std::max(t->p1().x, std::max(t->p2().x, t->p3().x));
        float maxy = std::max(t->p1().y, std::max(t->p2().y, t->p3().y));
        float maxz = std::max(t->p1().z, std::max(t->p2().z, t->p3().z));
        max.x = max.x < maxx ? maxx : max.x;
        max.y = max.y < maxy ? maxy : max.y;
        max.z = max.z < maxz ? maxz : max.z;
    }
    m_boundingBox.setBoundaries(min, max);
}

Mesh::Mesh(const std::string &filepath) {
    SolidTexture *texture = new SolidTexture(glm::vec3(0.5f, 0.5f, 0.5f));   
    Material material = { texture, 0.1f, 0.9f, 0.9f, 1.0f, 128 };
    
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
                m_polys.push_back(new Triangle(vertices[index[0] - 1], vertices[index[1] - 1], vertices[index[2] - 1], material));
            }
        }
    }
    computeBoundingBox();
}

RayIntersectData Mesh::rayIntersect(Ray ray) {   
    RayIntersectData result = {
        nullptr,
        INFINITY
    };

    if (m_boundingBox.rayIntersect(ray)) {  
        RayIntersectData intermediate;
        for (Triangle *t : m_polys) {
            intermediate = t->rayIntersect(ray);
            if (result.distance > intermediate.distance) {
                result.distance = intermediate.distance;
                result.sceneObject = intermediate.sceneObject;
            }
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
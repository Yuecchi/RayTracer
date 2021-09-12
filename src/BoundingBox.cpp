#include <cmath>
#include <algorithm>
#include <array>

#include "BoundingBox.hpp"

BoundingBox::BoundingBox() = default;

void BoundingBox::setBoundaries(const glm::vec3 &min, const glm::vec3 &max) {
    m_min = min;
    m_max = max;
}

bool BoundingBox::rayIntersect(Ray &ray) {
    glm::vec3 invdirection = 1.0f / ray.direction();

    std::array<float, 6> t = {
        (m_min.x - ray.origin().x) * invdirection.x,
        (m_max.x - ray.origin().x) * invdirection.x,

        (m_min.y - ray.origin().y) * invdirection.y,
        (m_max.y - ray.origin().y) * invdirection.y,

        (m_min.z - ray.origin().z) * invdirection.z,
        (m_max.z - ray.origin().z) * invdirection.z
    };
    std::sort(t.begin(), t.end());

    for (float d : t) {
        if (d < 0.0f) continue;
        glm::vec3 p = ray.origin() + (d * ray.direction());
        if (p.x > m_min.x && p.x < m_max.x && p.y > m_min.y && p.y < m_max.y) return true;
        if (p.z > m_min.z && p.z < m_max.z && p.y > m_min.y && p.y < m_max.y) return true;
        if (p.x > m_min.x && p.x < m_max.x && p.z > m_min.z && p.z < m_max.z) return true;
    }

    return false;
}

/*
bool BoundingBox::rayIntersect(Ray &ray) {
    float min = -INFINITY;
    float max = INFINITY;

    glm::vec3 invdirection = 1.0f / ray.direction();

    if (ray.direction().x == 0) {
        if (ray.origin().x < m_min.x || ray.origin().x > m_max.x) return false;
        else {
            float t1 = (m_min.x - ray.origin().x) * invdirection.x;
            float t2 = (m_max.x - ray.origin().x) * invdirection.x;
            if (t1 > t2) {
                // swap
                float temp = t1;
                t1 = t2;
                t2 = t1;
            }
            min = t1 > min ? t1 : min;
            max = t2 < max ? t2 : max;
            if (min > max) return false;
            if (max < 0.0f) return false;
        }
    }

    if (ray.direction().y == 0) {
        if (ray.origin().y < m_min.y || ray.origin().y > m_max.y) return false;
        else {
            float t1 = (m_min.y - ray.origin().y) * invdirection.y;
            float t2 = (m_max.y - ray.origin().y) * invdirection.y;
            if (t1 > t2) {
                // swap
                float temp = t1;
                t1 = t2;
                t2 = t1;
            }
            min = t1 > min ? t1 : min;
            max = t2 < max ? t2 : max;
            if (min > max) return false;
            if (max < 0.0f) return false;
        }
    }

    if (ray.direction().z == 0) {
        if (ray.origin().z < m_min.z || ray.origin().z > m_max.z) return false;
        else {
            float t1 = (m_min.z - ray.origin().z) * invdirection.z;
            float t2 = (m_max.z - ray.origin().z) * invdirection.z;
            if (t1 > t2) {
                // swap
                float temp = t1;
                t1 = t2;
                t2 = t1;
            }
            min = t1 > min ? t1 : min;
            max = t2 < max ? t2 : max;
            if (min > max) return false;
            if (max < 0.0f) return false;
        }
    }

    return true;
}
*/

BoundingBox::~BoundingBox() = default;
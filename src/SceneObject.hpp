#pragma once

#include "Ray.hpp"

struct RayIntersectData; 

class SceneObject {

    public:

        SceneObject();

        virtual RayIntersectData rayIntersect(Ray ray) = 0;  

        virtual ~SceneObject();

};

struct RayIntersectData {
    SceneObject *sceneObject;
    float distance;
};
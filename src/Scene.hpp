#pragma once

#include <vector>

#include "Camera.hpp"
#include "SceneObject.hpp"

#include "Sphere.hpp"
#include "Plane.hpp"
#include "Light.hpp"
#include "Triangle.hpp"
#include "Mesh.hpp"

class Scene {

    private:

        Camera m_camera;
        std::vector<SceneObject*> m_sceneObjects;
        std::vector<Light*> m_sceneLights;

    public:

        static Scene *createScene();

        void addObject(SceneObject *object);

        void addLight(Light *light);

        Camera &camera();

        std::vector<SceneObject*> &sceneObjects();

        std::vector<Light*> &sceneLights();

        void deleteScene();

};
#pragma once

#include <vector>

#include "Camera.hpp"
#include "Primitive.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Light.hpp"

class Scene {

    private:

        Camera m_camera;
        std::vector<Primitive*> m_sceneObjects;
        std::vector<Light*> m_sceneLights;

    public:

        static Scene *createScene();

        void addSphere(Sphere *sphere);

        void addPlane(Plane *plane);

        void addLight(Light *light);

        Camera &camera();

        std::vector<Primitive*> &sceneObjects();

        std::vector<Light*> &sceneLights();

        void deleteScene();

};
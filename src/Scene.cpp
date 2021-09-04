#include "Scene.hpp"

#include "Sphere.hpp"
#include "Plane.hpp"

Scene *Scene::createScene() {
    return new Scene;
}

void Scene::addSphere(Sphere *sphere) {
    m_sceneObjects.push_back(sphere);
}

void Scene::addPlane(Plane *plane) {
    m_sceneObjects.push_back(plane);   
}

void Scene::addLight(Light *light) {
    m_sceneLights.push_back(light);    
}


Camera &Scene::camera() {
    return m_camera;
}

std::vector<Primitive*> &Scene::sceneObjects() {
    return m_sceneObjects;
}

std::vector<Light*> &Scene::sceneLights() {
    return m_sceneLights;
}

void Scene::deleteScene() {
    // delete all scene objects and lights 
    // before deleting  the scene itself
    for (Primitive *p : m_sceneObjects) {
        delete p;
    }
    for (Light *light : m_sceneLights) {
        delete light;
    }
    delete this;
}
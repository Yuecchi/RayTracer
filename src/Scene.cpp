#include "Scene.hpp"

Scene *Scene::createScene() {
    return new Scene;
}

void Scene::addSphere(Sphere *sphere) {
    m_sceneObjects.push_back(sphere);
}

void Scene::addPlane(Plane *plane) {
    m_sceneObjects.push_back(plane);   
}

void Scene::addTriangle(Triangle *triangle) {
    m_sceneObjects.push_back(triangle);
}

void Scene::addMesh(Mesh *mesh) {
    m_sceneObjects.push_back(mesh);
}

void Scene::addLight(Light *light) {
    m_sceneLights.push_back(light);    
}

Camera &Scene::camera() {
    return m_camera;
}

std::vector<SceneObject*> &Scene::sceneObjects() {
    return m_sceneObjects;
}

std::vector<Light*> &Scene::sceneLights() {
    return m_sceneLights;
}

void Scene::deleteScene() {
    // delete all scene objects and lights 
    // before deleting  the scene itself
    for (SceneObject *p : m_sceneObjects) {
        delete p;
    }
    for (Light *light : m_sceneLights) {
        delete light;
    }
    delete this;
}
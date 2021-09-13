#include "Scene.hpp"

Scene *Scene::createScene() {
    return new Scene;
}

void Scene::addObject(SceneObject *object) {
    m_sceneObjects.push_back(object);
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
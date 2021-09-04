#include "Application.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include <GLFW/glfw3.h>

Application::Application(const char* name, unsigned int window_width, unsigned int window_height) : m_name(name) {
    m_window = new Window(name, window_width, window_height);
    Renderer::init(window_width, window_height);
    run();
}

void Application::run() {
    Scene *scene = Scene::createScene();
    scene->addSphere(new Sphere(glm::vec3(0.0f, -5.0f, -15.0f), 5.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
    scene->addSphere(new Sphere(glm::vec3(15.0f, -5.0f, -30.0f), 5.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(-25.0f, -5.0f, -50.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    scene->addSphere(new Sphere(glm::vec3(40.0f, -5.0f, -15.0f), 5.0f, glm::vec3(1.0f, 0.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(-20.0f, -5.0f, -15.0f), 5.0f, glm::vec3(0.0f, 1.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(25.0f, -5.0f, -20.0f), 5.0f, glm::vec3(1.0f, 1.0f, 0.0f)));
    scene->addPlane(new Plane(glm::vec3(0.0f, 1.0f, 0.0f), -10.0f, glm::vec3(0.1f, 0.1, 0.1f)));
    scene->addLight(new Light(glm::vec3(0.0f, 50.0f, -15.0f), 1000.0f));
    scene->addLight(new Light(glm::vec3(15.0f, -9.0f, -20.0f), 10.0f));

    while (!m_window->closed()) {
        m_window->poll();
        Renderer::clear();
        Renderer::drawScene(scene);
        m_window->update(); 
    }

    scene->deleteScene();

}

Application::~Application() {
    delete m_window;
};
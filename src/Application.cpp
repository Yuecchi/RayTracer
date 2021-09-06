#include "Application.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

Application::Application(const char* name, unsigned int window_width, unsigned int window_height) : m_name(name) {
    m_window = new Window(name, window_width, window_height);
    Renderer::init(window_width, window_height);
    run();
}

void Application::run() {

    srand(time(NULL));
    clock_t timeElapsed;
    clock_t currentTime;

    Scene *scene = Scene::createScene();

    /*
    for (int i = 0; i < 150; i += 1) {
        scene->addSphere(new Sphere(glm::vec3(-100 + (rand() % 200), -5 + (rand() % 100), -200 + (rand() % 200)), 5.0f, glm::vec3(rand() % 2, rand() % 2, rand() % 2)));
    }
    scene->addLight(new Light(glm::vec3(20.0f, 0.0f, -50.0f), 1000.0f));
    scene->addPlane(new Plane(glm::vec3(0.0f, 1.0f, 0.0f), -10.0f, glm::vec3(0.1f, 0.1f, 0.1f)));
    */

    scene->addSphere(new Sphere(glm::vec3(0.0f, -5.0f, -15.0f), 5.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
    scene->addSphere(new Sphere(glm::vec3(15.0f, -5.0f, -30.0f), 5.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(-25.0f, -5.0f, -50.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    scene->addSphere(new Sphere(glm::vec3(40.0f, -5.0f, -15.0f), 5.0f, glm::vec3(1.0f, 0.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(-20.0f, -5.0f, -15.0f), 5.0f, glm::vec3(0.0f, 1.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(25.0f, -5.0f, -20.0f), 5.0f, glm::vec3(1.0f, 1.0f, 0.0f)));
    scene->addPlane(new Plane(glm::vec3(0.0f, 1.0f, 0.0f), -10.0f, glm::vec3(0.1f, 0.1f, 0.1f)));
    scene->addLight(new Light(glm::vec3(0.0f, 50.0f, -15.0f), 1000.0f));
    scene->addLight(new Light(glm::vec3(15.0f, -9.0f, -20.0f), 10.0f));

    while (!m_window->closed()) {
        m_window->poll();
        Renderer::clear();
        timeElapsed = clock();
        Renderer::drawScene(scene);
        //scene->camera().rotate(3.141f / 45.0f);
        currentTime = clock();
        std::cout << 1.0f / ((float)(currentTime - timeElapsed)/CLOCKS_PER_SEC) << "\n";
        m_window->update(); 
    }

    scene->deleteScene();

}

Application::~Application() {
    delete m_window;
};
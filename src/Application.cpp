#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>

#include "Application.hpp" 
#include "Scene.hpp"
#include "Renderer.hpp" 

Application::Application(const char* name, unsigned int window_width, unsigned int window_height) : m_name(name) {
    m_window = new Window(name, window_width, window_height);
    Renderer::init(window_width, window_height);
    run();
}

void Application::run() {

    srand(time(NULL));
    
    Scene *scene = Scene::createScene(); 

    /*
    for (int i = 0; i < 100; i += 1) {
        scene->addSphere(new Sphere(glm::vec3(-100 + (rand() % 200), -5 + (rand() % 100), -100 + (rand() % 200)), 5.0f, glm::vec3(rand() % 2, rand() % 2, rand() % 2)));
    }
    scene->addLight(new Light(glm::vec3(20.0f, 0.0f, 0.0f), 1000.0f));
    scene->addPlane(new Plane(glm::vec3(0.0f, 1.0f, 0.0f), -10.0f, glm::vec3(0.1f, 0.1f, 0.1f)));
    */

    scene->addSphere(new Sphere(glm::vec3(0.0f, -5.0f, -50.0f), 5.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
    scene->addSphere(new Sphere(glm::vec3(-25.0f, -5.0f, -55.0f), 5.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(-18.0f, -5.0f, -80.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f))); 
    scene->addSphere(new Sphere(glm::vec3(20.0f, -5.0f, -20.0f), 5.0f, glm::vec3(1.0f, 0.0f, 1.0f)));
    scene->addSphere(new Sphere(glm::vec3(-25.0f, -5.0f, -30.0f), 5.0f, glm::vec3(0.0f, 1.0f, 1.0f)));  
    scene->addSphere(new Sphere(glm::vec3(20.0f, -5.0f, -50.0f), 5.0f, glm::vec3(1.0f, 1.0f, 0.0f)));

    scene->addTriangle(new Triangle(
        glm::vec3(-35.0f, 0.0f, -100.0f),
        glm::vec3(0.0f, 50.0f, -80.0f),
        glm::vec3(35.0f, 0.0f, -100.0f),
        glm::vec3(0.0)
        ));  

    scene->addPlane(new Plane(glm::vec3(0.0f, 1.0f, 0.0f), -10.0f, glm::vec3(0.1, 0.1, 0.1)));
    scene->addLight(new Light(glm::vec3(0.0f, 50.0f, -75.0f), 5000.0f));
    scene->addLight(new Light(glm::vec3(10.0f, -9.0f, -30.0f), 10.0f));

    while (!m_window->closed()) {
        m_window->poll();
        Renderer::clear();
        
        auto start = std::chrono::system_clock::now();
        
        Renderer::drawScene(scene);
        //scene->camera().rotate(3.141f / 15.0f);
        
        auto end = std::chrono::system_clock::now();
        auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << 1.0f / (timeElapsed.count() / 1e+6) << "\n";
        
        m_window->update(); 
    }

    scene->deleteScene();

}

Application::~Application() {
    delete m_window;
};
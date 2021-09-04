#include <iostream>

#include "Window.hpp"

bool Window::s_glfw_init = false;

Window::Window(const char* title, unsigned int width, unsigned int height) : m_title(title), m_width(width), m_height(height) { 
    // initialize glfw once, and only once
    if (!s_glfw_init) {
        if (!glfwInit()) {
            std::cout << "Failed to initialize GLFW\n";
            exit(EXIT_FAILURE);
        }
        std::cout << "GLFW initialized\n";
        s_glfw_init = true;
    }
    // create the window for the application
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_window) {
        std::cout << "Window failed to create\n";
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_window);
}

void Window::update() {
    glfwSwapBuffers(m_window);
}

void Window::poll() {
    glfwPollEvents();
}

bool Window::closed() {
    return glfwWindowShouldClose(m_window);
}

Window::~Window()  {
    glfwDestroyWindow(m_window);
}
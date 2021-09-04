#pragma once

#include <GLFW/glfw3.h>

class Window {

    private:

        static bool s_glfw_init;
        GLFWwindow *m_window;

        const char *m_title;
        unsigned int m_width;
        unsigned int m_height;

    public:

        Window(const char* title, unsigned int width, unsigned int height);

        void update();

        void poll();

        bool closed();

        ~Window();

};
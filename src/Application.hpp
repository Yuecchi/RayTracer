#pragma once

#include "Window.hpp"

class Application {

    private:

        Window *m_window;
        const char *m_name;
        
    public:

        Application(const char *name, unsigned int window_width, unsigned int window_height);

        void run();

        ~Application();

};
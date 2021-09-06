#pragma once

#include "Scene.hpp"
#include "Ray.hpp"

class Renderer {

    private:

        static bool s_init;
        static unsigned int s_canvas_width;
        static unsigned int s_canvas_height;
        static Ray s_ray;

    public:

        Renderer() = delete;

        ~Renderer() = delete;

        static void init(unsigned int canvas_width, unsigned int canvas_height);

        static void clear();
        
        static void drawScene(Scene *scene);

        static void put_pixel(float x, float y, const glm::vec3 &color);

};
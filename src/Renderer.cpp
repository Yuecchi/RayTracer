#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Renderer.hpp"
#include "Primitive.hpp"
#include "Light.hpp"

bool Renderer::s_init = false;
unsigned int Renderer::s_canvas_width;
unsigned int Renderer::s_canvas_height;
Ray Renderer::s_ray;

glm::vec3 trace(Ray *ray, Scene *scene, unsigned int depth);
glm::vec3 shade(Ray *ray, Scene *scene, Primitive *hitObject, float hitDistance, unsigned int depth);

void Renderer::init(unsigned int canvas_width, unsigned int canvas_height) {
    if (!s_init) {
        if (glewInit() != GLEW_OK) {
            std::cout <<  "Failed to initialize GLEW\n";
            exit(EXIT_FAILURE);
        }
        std::cout <<  "GLEW Initialized\n";
        s_init = true;
    }
    s_canvas_width = canvas_width;
    s_canvas_height = canvas_height;
    glOrtho(0.0, (double)canvas_width, (double)canvas_height, 0.0, 0.0, 1.0);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

glm::vec3 trace(Ray *ray, Scene *scene, unsigned int depth) {
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f); // background color
    float hitDistance = INFINITY;
    Primitive *hitObject = nullptr;
    for (Primitive *p : scene->sceneObjects()) {
        float distance = p->rayIntersect(ray);
        if (distance < hitDistance) {
            hitDistance = distance;
            hitObject = p;
        }
    }
    if (hitDistance == INFINITY) return color; // no object found by ray
    else return shade(ray, scene, hitObject, hitDistance, depth);
}

glm::vec3 shade(Ray *ray, Scene * scene, Primitive *hitObject, float hitDistance, unsigned int depth) {
    static const float bias = 1e-4;
    glm::vec3 color = 0.1f * hitObject->color(); // ambient
    glm::vec3 hitPos = ray->origin() + (ray->direction() * hitDistance);
    glm::vec3 surfaceNormal = hitObject->normal(hitPos);
    for (Light *light : scene->sceneLights()) {
        float distanceFromLight = glm::distance(light->position(), hitPos);
        Ray lightRay;
        lightRay.setDirection(light->position() - hitPos);
        lightRay.setOrigin(hitPos + (bias * surfaceNormal));
        bool obstructed = false;
        for (Primitive *p : scene->sceneObjects()) {
            float obstruction = p->rayIntersect(&lightRay);
            if (obstruction != INFINITY && (distanceFromLight - obstruction) > bias) {
                obstructed = true;
                break;
            }
        }
        if (!obstructed) {
            float attenuation = (1.0f / pow(distanceFromLight, 2)) * light->intensity();  
            float incidence = glm::dot(surfaceNormal, hitObject->normal(light->position())); 
            attenuation = attenuation > 1.0f ? 1.0f : attenuation;
            color += hitObject->color() * (attenuation * incidence);
        }
    }
    // reflection
    if (depth > 0) {
        Ray reflectRay;
        reflectRay.setDirection(glm::reflect(ray->direction(), surfaceNormal));
        reflectRay.setOrigin(hitPos + (bias * reflectRay.direction()));
        color += trace(&reflectRay, scene, depth - 1);
    }

    return color;
}

void Renderer::drawScene(Scene *scene) {

    float aspect = (float)s_canvas_width / (float)s_canvas_height;

    // setup canvas
    glm::vec3 canvas_center = scene->camera().direction();
    glm::vec3 canvas_top_left = (canvas_center - scene->camera().right() + scene->camera().up());
    glm::vec3 canvas_top_right = (canvas_center + scene->camera().right() + scene->camera().up());
    glm::vec3 canvas_bottom_left = canvas_top_left - (2.0f * scene->camera().up());

    // calculate increments by which the ray will be redirected by
    // in order to fire through each pixel
    glm::vec3 right_increment = (((canvas_top_right - canvas_top_left) / (float)s_canvas_width)) * aspect;
    glm::vec3 down_increment  = ((canvas_bottom_left - canvas_top_left) / (float)s_canvas_height);
    
    glm::vec3 verticalOffset, horizontalOffset, direction;
    glBegin(GL_POINTS);
    s_ray.setOrigin(scene->camera().position());
    for (int y = 0; y < s_canvas_height; y += 1) {
        verticalOffset = (float)y * down_increment;
        for (int x = 0; x < s_canvas_width; x += 1) {
            horizontalOffset = (float)x * right_increment;
            direction = canvas_top_left + verticalOffset + horizontalOffset;
            s_ray.setDirection(direction);
            put_pixel(x, y, trace(&s_ray, scene, 4));
        }
    }
    glEnd();
}

void Renderer::put_pixel(float x, float y, const glm::vec3 &color) {  
    glColor3f(color.r, color.g, color.b);
    glVertex2f(x, y);
}


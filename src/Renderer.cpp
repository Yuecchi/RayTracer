#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Renderer.hpp"
#include "Primitive.hpp"
#include "Light.hpp"

struct ObjectManifold {
    Primitive *object;
    float distance;
};


bool Renderer::s_init = false;
unsigned int Renderer::s_canvas_width;
unsigned int Renderer::s_canvas_height;
Ray Renderer::s_ray;

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

ObjectManifold traceObjects(Ray *ray, Scene *scene) {
    ObjectManifold result;
    result.distance = INFINITY;
    result.object = nullptr;
    for (Primitive *p : scene->sceneObjects()) {
        float distance = p->rayIntersect(ray);
        if (distance < result.distance) {
            result.distance = distance;
            result.object = p;
        }
    }
    return result;
}

glm::vec3 traceLight(Ray *ray, Scene *scene, ObjectManifold currentObject) {
    static const float bias = 1e-4;  
    float illumination = 0.0f;
    glm::vec3 ambientLight = 0.1f * currentObject.object->color();
    glm::vec3 surfacePoint  = ray->origin() + (ray->direction() * currentObject.distance);
    glm::vec3 surfaceNormal = currentObject.object->normal(surfacePoint); 
    for (Light *light : scene->sceneLights()) {
        Ray shadowRay;
        shadowRay.setDirection(light->position() - surfacePoint);
        shadowRay.setOrigin(surfacePoint + (bias * surfaceNormal));
        float distanceFromLight = glm::distance(light->position(), surfacePoint);
        bool obstructed = false;
        for (Primitive *p : scene->sceneObjects()) {
            float obstruction = p->rayIntersect(&shadowRay);
            if (obstruction != INFINITY && (distanceFromLight - obstruction) > bias) {
                obstructed = true;
                break;
            }
        }
        if (!obstructed) {
            float attenuation = (1.0f / pow(distanceFromLight, 2)) * light->intensity();  
            float incidence = glm::dot(surfaceNormal, currentObject.object->normal(light->position())); 
            attenuation = attenuation > 1.0f ? 1.0f : attenuation;
            illumination += attenuation * incidence;
        }
    }
    return ambientLight + (currentObject.object->color() * illumination);
}

void Renderer::drawScene(Scene *scene) {

    float aspect = (float)s_canvas_width / (float)s_canvas_height;

    // setup canvas
    glm::vec3 canvas_center = scene->camera().position() + scene->camera().direction();
    glm::vec3 canvas_top_left = (canvas_center - scene->camera().right() + scene->camera().up());
    glm::vec3 canvas_top_right = (canvas_center + scene->camera().right() + scene->camera().up());
    glm::vec3 canvas_bottom_left = canvas_top_left - (2.0f * scene->camera().up());

    // calculate increments by which the ray will be redirected by
    // in order to fire through each pixel
    glm::vec3 right_increment = (((canvas_top_right - canvas_top_left) / (float)s_canvas_width)) * aspect;
    glm::vec3 down_increment  = ((canvas_bottom_left - canvas_top_left) / (float)s_canvas_height);
    
    s_ray.setOrigin(scene->camera().position());
    for (int y = 0; y < s_canvas_height; y += 1) {
        glm::vec3 verticalOffset = (float)y * down_increment;
        for (int x = 0; x < s_canvas_width; x += 1) {
            glm::vec3 horizontalOffset = (float)x * right_increment;
            s_ray.setDirection(canvas_top_left + verticalOffset + horizontalOffset);
            ObjectManifold closestObject = traceObjects(&s_ray, scene);
            
            // calculate the light contribution to the pixel
            if (closestObject.distance != INFINITY) {
                
                // compute portion of pixel colour based colour ccontribution 
                // from light sources
                glm::vec3 surfaceColor = traceLight(&s_ray, scene, closestObject);

                // calculate angle of reflection
                float bias = 1e-4;
                glm::vec3 hitPos = s_ray.origin() + (s_ray.direction() * closestObject.distance);
                glm::vec3 surfaceNormal = closestObject.object->normal(hitPos);                
                Ray reflectRay;
                reflectRay.setDirection(glm::reflect(s_ray.direction(), surfaceNormal));
                reflectRay.setOrigin(hitPos + (bias * reflectRay.direction()));

                // compute porition of pixel colour based on color contribution 
                // from surrounding objects (reflection)
                ObjectManifold reflectObject = traceObjects(&reflectRay, scene);
                if (reflectObject.distance != INFINITY) {
                    glm::vec3 reflectColor = traceLight(&reflectRay, scene, reflectObject);
                    // color pixel with both color contributions
                    Renderer::put_pixel(x, y, (0.5f * reflectColor) + surfaceColor);
                } else {
                    // color pixel with single color contribution
                    Renderer::put_pixel(x, y, surfaceColor);
                }
            }
        }
    }
}

void Renderer::put_pixel(float x, float y, glm::vec3 color) {
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    glVertex2f(x, y);
    glEnd();
}


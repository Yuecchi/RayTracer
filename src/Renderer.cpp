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

void Renderer::drawScene(Scene *scene) {

    float aspect = (float)s_canvas_width / (float)s_canvas_height;

    // setup canvas
    glm::vec3 canvas_center = scene->camera().position() + scene->camera().direction();
    glm::vec3 canvas_top_left = (canvas_center - scene->camera().right() + scene->camera().up());
    glm::vec3 canvas_top_right = (canvas_center + scene->camera().right() + scene->camera().up());
    glm::vec3 canvas_bottom_left = canvas_top_left - (2.0f * scene->camera().up());

    // calculate increments by which the ray will be redirected by
    // in order to fire through each pixel
    glm::vec3 right_increment = ((canvas_top_right - canvas_top_left) / (float)s_canvas_width) * aspect;
    glm::vec3 down_increment  = (canvas_bottom_left - canvas_top_left) / (float)s_canvas_height;
    
    s_ray.setOrigin(scene->camera().position());
    for (int y = 0; y < s_canvas_height; y += 1) {
        glm::vec3 verticalOffset = (float)y * down_increment;
        for (int x = 0; x < s_canvas_width; x += 1) {
            glm::vec3 horizontalOffset = (float)x * right_increment;
            s_ray.setDirection(canvas_top_left + verticalOffset + horizontalOffset);
            float closest = INFINITY;
            Primitive *sceneObject = nullptr;
            for (Primitive *p : scene->sceneObjects()) {
                float intersect_distance = p->rayIntersect(&s_ray);
                if (intersect_distance < closest) {
                    closest = intersect_distance;
                    sceneObject = p;
                }
            }
            // calculate the light contribution to the pixel
            if (closest != INFINITY) {  
                glm::vec3 hitPos = s_ray.origin() + (s_ray.direction() * closest);
                glm::vec3 surfaceNormal = sceneObject->normal(hitPos);
                float bias = 1e-4;
                float ambience = 0.1f;
                float hue = 0.0f;
                float reflectHue = 0.0f;

                // calculate angle of reflection
                Ray reflectRay;
                reflectRay.setDirection(glm::reflect(s_ray.direction(), surfaceNormal));
                reflectRay.setOrigin(hitPos + (bias * reflectRay.direction()));
                float reflect = INFINITY;
                Primitive *reflectObject = nullptr;
                for (Primitive *p : scene->sceneObjects()) {
                    float reflect_distance = p->rayIntersect(&reflectRay);
                    if (reflect_distance < reflect) {
                        reflect = reflect_distance;
                        reflectObject = p;
                    }
                }      

                for (Light *light : scene->sceneLights()) {
                    if (reflect != INFINITY) {
                        glm::vec3 reflectPos = hitPos + (reflectRay.direction() * reflect);
                        glm::vec3 reflectSurfaceNormal = reflectObject->normal(reflectPos);
                        float reflect_distance_from_light = glm::distance(light->position(), hitPos);
                        Ray reflectShadowRay;
                        reflectShadowRay.setDirection(light->position() - reflectPos);
                        reflectShadowRay.setOrigin(reflectPos + (bias * reflectSurfaceNormal));
                        bool reflectObstructed = false;
                        for (Primitive *p : scene->sceneObjects()) {
                            float reflectObstruction = p->rayIntersect(&reflectShadowRay);
                            if (reflectObstruction != INFINITY && (reflect_distance_from_light - reflectObstruction) > bias){
                                reflectObstructed = true;
                                break;
                            }
                        }
                        if (!reflectObstructed) {
                            float attenuation = (1.0f / pow(reflect_distance_from_light, 2)) * light->intensity();
                            attenuation = attenuation > 1.0f ? 1.0f : attenuation;
                            float incidence = glm::dot(reflectSurfaceNormal, reflectObject->normal(light->position()));
                            reflectHue += attenuation * incidence; 
                        }
                    }

                    float distance_from_light = glm::distance(light->position(), hitPos);
                    Ray shadowRay;
                    shadowRay.setDirection(light->position() - hitPos);
                    shadowRay.setOrigin(hitPos + (bias * surfaceNormal));
                    bool obstructed = false;
                    for (Primitive *p : scene->sceneObjects()) {
                        float obstruction = p->rayIntersect(&shadowRay); 
                        if (obstruction != INFINITY && (distance_from_light - obstruction) > bias) {
                            obstructed = true;
                            break;
                        }
                    }
                    if (!obstructed) {
                        float attenuation = (1.0f / pow(distance_from_light, 2)) * light->intensity();
                        attenuation = attenuation > 1.0f ? 1.0f : attenuation;
                        float incidence = glm::dot(surfaceNormal, sceneObject->normal(light->position()));
                        hue += attenuation * incidence;   
                    }
                }
                hue = hue < ambience ? ambience : hue;
                if (reflect != INFINITY) {
                    Renderer::put_pixel(x, y, (reflectObject->color() * reflectHue) + (sceneObject->color() * hue));
                } else {
                    Renderer::put_pixel(x, y, sceneObject->color() * hue);
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
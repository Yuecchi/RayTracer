#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <functional>

#include "Scene.hpp"
#include "Ray.hpp"

struct Job {
    std::function<glm::vec3(Ray&, Scene*, unsigned int)> func;
    Ray ray;
    glm::vec3 directionComponents[3];
    Scene *scene;
    unsigned int depth;
    glm::vec3 *color;
};

class ThreadPool {

    private:

        std::mutex m_mutex;
        std::condition_variable m_cond;

        std::mutex *m_mainMutex;
        std::condition_variable *m_mainCond;

        std::vector<std::thread> m_threads;
        std::queue<Job*> m_jobs;
        static const unsigned int MAX_THREADS = 16;

        std::atomic<int> m_jobsCompleted;

        void run() {
            Job *job;
            while (true) {
                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_cond.wait(lock, [this](){ return !m_jobs.empty(); });
                    job = m_jobs.front();
                    m_jobs.pop();
                }

                job->ray.setDirection(job->directionComponents[0] + job->directionComponents[1] + job->directionComponents[2]);
                *(job->color) = job->func(job->ray, job->scene, job->depth);
                m_jobsCompleted++;
                if (m_jobsCompleted == 1280 * 720) {
                    m_mainCond->notify_one();
                }
            }
        }

    public:

        ThreadPool() = default;

        void start(std::mutex *mutex, std::condition_variable *cond) {
            m_jobsCompleted = 0;
            m_mainMutex = mutex;
            m_mainCond = cond;

            for (int i = 0; i < MAX_THREADS; i  += 1) {
                m_threads.push_back(std::thread(&ThreadPool::run, this));
            }

        }

        void submit(Job *job) {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_jobs.push(job);
            }
            m_cond.notify_one();
        }

        int jobsCompleted() {
            return m_jobsCompleted.load();
        }

        void resetJobCount() {
            m_jobsCompleted = 0;
        }

        ~ThreadPool() = default;

};

class Renderer {

    private:

        static bool s_init;
        static unsigned int s_canvas_width;
        static unsigned int s_canvas_height;
        static Ray s_ray;
        
        static ThreadPool s_threadPool;
        static std::mutex s_mutex;
        static std::condition_variable s_cond;

        static glm::vec3 s_buffer[1280][720];

    public:

        Renderer() = delete;

        ~Renderer() = delete;

        static void init(unsigned int canvas_width, unsigned int canvas_height);

        static void clear();
        
        static void drawScene(Scene *scene);

        static void put_pixel(float x, float y, const glm::vec3 &color);

};
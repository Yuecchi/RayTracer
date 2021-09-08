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

        static const unsigned int MAX_THREADS = 4;
        std::vector<std::thread> m_threads;
        std::queue<Job*> m_jobQueue[MAX_THREADS];    

        std::atomic<int> m_jobsCompleted;
        int m_jobSize; 

        void run(std::queue<Job*> *jobQueue) {
            Job *job;

            while (true) {
                // if the thread is not currently working, it will simply
                // wait until it is notified to do so by the main thread,
                // which will happen when all work queues have been filled.
                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_cond.wait(lock);
                }
                while (!jobQueue->empty()) {
                    // the thread will now proceed to complete all jobs 
                    // within its work queue
                    job = jobQueue->front();
                    jobQueue->pop();
                    job->ray.setDirection(job->directionComponents[0] + job->directionComponents[1] + job->directionComponents[2]);
                    *(job->color) = job->func(job->ray, job->scene, job->depth);  
                    // every time a job is completed a counter tracking the 
                    // total work done is incremented. Once all jobs have 
                    // been completed the main thread will be notified.
                    m_jobsCompleted++;
                    if (m_jobsCompleted == m_jobSize) {
                        m_mainCond->notify_one();
                    }
                }
            }
        }

    public:

        ThreadPool() = default;

        void start(std::mutex *mutex, std::condition_variable *cond, int jobSize) {
            m_jobsCompleted = 0;
            m_mainMutex     = mutex;
            m_mainCond      = cond;
            m_jobSize       = jobSize;
            for (int i = 0; i < MAX_THREADS; i  += 1) {
                m_threads.push_back(std::thread(&ThreadPool::run, this, &m_jobQueue[i]));
            }
        }

        void submit(Job *job) {
            static int jobsSent = 0;
            static int currentQueue = 0;
            m_jobQueue[currentQueue].push(job);
            currentQueue = (currentQueue + 1) % MAX_THREADS;
            jobsSent++;
            if (jobsSent == m_jobSize) {
                m_cond.notify_all();
                jobsSent = 0;
            }
        }

        int jobsCompleted() {
            return m_jobsCompleted.load();
        }

        int jobSize() {
            return m_jobSize;
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

        static glm::vec3 **s_buffer;
        static Job **s_jobs;

    public:

        Renderer() = delete;

        ~Renderer() = delete;

        static void init(unsigned int canvas_width, unsigned int canvas_height);

        static void clear();
        
        static void drawScene(Scene *scene);

        static void put_pixel(float x, float y, const glm::vec3 &color);

};
#include "Application.hpp"

#include <thread>
#include <iostream>

int main() {

    std::cout << std::thread::hardware_concurrency << "\n"; 
    Application raytracer("Raytracer", 960, 540);
    
    return 0;
}
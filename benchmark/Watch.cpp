#include "Watch.hpp"

void Watch::start(){
    time = std::chrono::high_resolution_clock::now(); 
}
double Watch::stop(){
    auto now =  std::chrono::high_resolution_clock::now();
    auto elapsed = now - time;
    std::chrono::duration<double> elapsed_seconds = elapsed;
    time = std::chrono::time_point<std::chrono::high_resolution_clock>();

    return elapsed_seconds.count();
}

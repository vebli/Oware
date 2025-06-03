#pragma once
#include <chrono>
#include <iostream>

class Watch{
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
public:
    void start();
    double stop();
private:
    TimePoint time;
};

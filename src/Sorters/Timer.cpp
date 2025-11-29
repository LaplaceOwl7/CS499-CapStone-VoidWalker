#include <chrono>

#include "Sorters/Timer.hpp"

// Starts a timer
void Timer::startTimer(){
    m_start = std::chrono::high_resolution_clock::now();
}

// Stops the time and returns the variable
long long Timer::stopTimer(){
    auto m_end = std::chrono::high_resolution_clock::now();

    // Subtract to find out duration
    return std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count();
}

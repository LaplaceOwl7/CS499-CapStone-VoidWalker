#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
public:
    /// @brief Starts a timer using the chrono method
    void startTimer();
    /// @brief  Stops the timer started by `startTime()`
    /// @return a long long that is the time between startTime() and stopTime()
    long long stopTimer();

private:
    std::chrono::high_resolution_clock::time_point m_start;
};

#endif // TIMER_HPP

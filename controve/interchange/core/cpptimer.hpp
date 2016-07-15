#ifndef __INTERCHANGE_CPPTIMER_H
#define __INTERCHANGE_CPPTIMER_H

#include "timer.hpp"
#include <chrono>

class CppTimer : public Timer {
public:
    CppTimer();
    Timer::milliseconds getTime();
    typedef std::chrono::high_resolution_clock Clock;

private:
    Clock::time_point beginTime;
    //Timer::milliseconds elapsedTime;
};
#endif

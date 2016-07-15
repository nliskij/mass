#include "cpptimer.hpp"
#include <math.h>
#include <utility>

CppTimer::CppTimer() { beginTime = Clock::now(); }
Timer::milliseconds CppTimer::getTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - beginTime)
        .count();
}

#include <utility>

class Timer {
public:
    typedef float milliseconds;
    virtual milliseconds getTime() = 0;
};

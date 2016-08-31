#ifndef CONTROVE_COMMON_THREADING_TIMED_LOOP_H_
#define CONTROVE_COMMON_THREADING_TIMED_LOOP_H_

#include "controve/common/time.hpp"

namespace controve {
namespace time {

class TimedLoop {
  public:
    TimedLoop(const Time &period, const Time &phase = Time::ZERO)
      : period_(period), phase_(phase), last_time_(phase) {
        resetIterations();
    }

    void resetIterations(const Time &now = Time::now()) { loop(now - period_); }

    int loop(const Time &now = Time::now());

    int sleepFullCycle() {
      const int r = loop(Time::now());
      sleepUntil(sleepTime());
      return r;
    }

    const Time &sleepTime() const { return last_time_; }

  private:
      const Time period_, phase_;

      Time last_time_ = Time::ZERO;
};

}  // namespace time
}  // namespace controve

#endif  // CONTROVE_COMMON_THREADING_TIMED_LOOP_H_

#include "controve/common/threading/timed_loop.hpp"

namespace controve {
namespace time {

int TimedLoop::loop(const Time &now) {
  // 1. Floor the value ((now - phase) / 400) * 400)
  // 2. Add the period if we've had a single cycle
  // 3. Add the phase
  const Time next_time = Time::inNSecs(((now - phase_).toNSecs() + 1) /
      period_.toNSecs() * period_.toNSecs()) +
      ((now < phase_) ? Time::ZERO : period_) + phase_;

  const Time difference = next_time - last_time_;
  const int result = difference.toNSecs() / period_.toNSecs();
  last_time_ = next_time;
  return result;
}

}  // namespace time
}  // namespace controve

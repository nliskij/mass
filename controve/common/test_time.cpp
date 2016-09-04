#include "controve/common/time.hpp"

#include "gtest/gtest.h"

namespace controve {
namespace timing {
namespace testing {

TEST(TimeTest, MonotonicClock) {
  monotonic_clock::time_point start = monotonic_clock::now();
  const auto sleepTime = ::std::chrono::milliseconds(500);
  ::std::this_thread::sleep_until(start + sleepTime);
  monotonic_clock::time_point end = monotonic_clock::now();
  EXPECT_GE(end - start, sleepTime);
  EXPECT_LT(end - start, sleepTime + std::chrono::milliseconds(200));
}

}  // namespace testing
}  // namespace timing
}  // namespace controve

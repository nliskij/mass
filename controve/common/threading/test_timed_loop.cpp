#include "controve/common/threading/timed_loop.hpp"

#include "gtest/gtest.h"

#include <iostream>

namespace controve {
namespace timing {
namespace testing {

using nsecs = ::std::chrono::nanoseconds;
using msecs = ::std::chrono::milliseconds;
using usecs = ::std::chrono::microseconds;
using secs = ::std::chrono::seconds;
using time = monotonic_clock::time_point;

TEST(TimedLoopTest, resetIterations) {
  using ::controve::timing::monotonic_clock;

  {
    TimedLoop loop(msecs(200));

    loop.resetIterations(monotonic_clock::epoch());
    EXPECT_EQ(monotonic_clock::epoch(), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(monotonic_clock::epoch()));
    EXPECT_EQ(time(msecs(200)), loop.sleepTime());

    loop.resetIterations(time(msecs(199)));
    EXPECT_EQ(time(msecs(0)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(monotonic_clock::epoch()));
    EXPECT_EQ(time(msecs(200)), loop.sleepTime());

    loop.resetIterations(time(msecs(200)));
    EXPECT_EQ(time(msecs(200)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(399))));
    EXPECT_EQ(time(msecs(400)), loop.sleepTime());

    loop.resetIterations(time(msecs(201)));
    EXPECT_EQ(time(msecs(200)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(201))));
    EXPECT_EQ(time(msecs(400)), loop.sleepTime());
  }
  {
    TimedLoop loop(msecs(200), msecs(1));
    loop.resetIterations(time(msecs(0)));
    EXPECT_EQ(time(msecs(-199)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(0))));
    EXPECT_EQ(time(msecs(1)), loop.sleepTime());
  }
  {
    TimedLoop loop(msecs(200), msecs(199));

    loop.resetIterations(time(msecs(0)));
    EXPECT_EQ(time(msecs(-1)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(0))));
    EXPECT_EQ(time(msecs(199)), loop.sleepTime());

    loop.resetIterations(time(msecs(198)));
    EXPECT_EQ(time(msecs(-1)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(198))));
    EXPECT_EQ(time(msecs(199)), loop.sleepTime());

    loop.resetIterations(time(msecs(199)));
    EXPECT_EQ(time(msecs(199)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(199))));
    EXPECT_EQ(time(msecs(399)), loop.sleepTime());

    loop.resetIterations(time(msecs(200)));
    EXPECT_EQ(time(msecs(199)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(200))));
    EXPECT_EQ(time(msecs(399)), loop.sleepTime());
  }
}

TEST(TimedLoopTest, loop) {
  {
    TimedLoop loop(msecs(200), msecs(199));
    loop.resetIterations(time(msecs(0)));
    EXPECT_EQ(1, loop.loop(time(msecs(0))));
    EXPECT_EQ(time(msecs(199)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(200))));
    EXPECT_EQ(time(msecs(399)), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(time(msecs(200))));
    EXPECT_EQ(time(msecs(399)), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(time(msecs((201)))));
    EXPECT_EQ(time(msecs(399)), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(time(msecs(398))));
    EXPECT_EQ(time(msecs(399)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(399))));
    EXPECT_EQ(time(msecs(599)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(600))));
    EXPECT_EQ(time(msecs(799)), loop.sleepTime());
    EXPECT_EQ(3, loop.loop(time(msecs(1200))));
    EXPECT_EQ(time(msecs(1399)), loop.sleepTime());
  }
  {
    TimedLoop loop(msecs(50), msecs(1));
    loop.resetIterations(time(msecs(0)));
    EXPECT_EQ(1, loop.loop(time(msecs(0))));
    EXPECT_EQ(time(msecs(1)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(50))));
    EXPECT_EQ(time(msecs(51)), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(time(msecs(50))));
    EXPECT_EQ(time(msecs(51)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(53))));
    EXPECT_EQ(time(msecs(101)), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(time(msecs(98))));
    EXPECT_EQ(time(msecs(101)), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(time(msecs(100))));
    EXPECT_EQ(time(msecs(101)), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(time(msecs(101))));
    EXPECT_EQ(time(msecs(151)), loop.sleepTime());
  }
}

}  // namespace testing
}  // namespace time
}  // namespace controve

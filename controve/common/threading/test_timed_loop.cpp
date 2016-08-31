#include "controve/common/threading/timed_loop.hpp"

#include "gtest/gtest.h"

namespace controve {
namespace time {
namespace testing {

TEST(TimedLoopTest, resetIterations) {
  {
    TimedLoop loop(Time::inMSecs(200));

    loop.resetIterations(Time::ZERO);
    EXPECT_EQ(Time::inMSecs(0), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::ZERO));
    EXPECT_EQ(Time::inMSecs(200), loop.sleepTime());

    loop.resetIterations(Time::inMSecs(199));
    EXPECT_EQ(Time::inMSecs(0), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::ZERO));
    EXPECT_EQ(Time::inMSecs(200), loop.sleepTime());

    loop.resetIterations(Time::inMSecs(200));
    EXPECT_EQ(Time::inMSecs(200), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(399)));
    EXPECT_EQ(Time::inMSecs(400), loop.sleepTime());

    loop.resetIterations(Time::inMSecs(201));
    EXPECT_EQ(Time::inMSecs(200), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(201)));
    EXPECT_EQ(Time::inMSecs(400), loop.sleepTime());
  }
  {
    TimedLoop loop(Time::inMSecs(200), Time::inMSecs(1));
    loop.resetIterations(Time::ZERO);
    EXPECT_EQ(Time::inMSecs(-199), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::ZERO));
    EXPECT_EQ(Time::inMSecs(1), loop.sleepTime());
  }
  {
    TimedLoop loop(Time::inMSecs(200), Time::inMSecs(199));

    loop.resetIterations(Time::ZERO);
    EXPECT_EQ(Time::inMSecs(-1), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::ZERO));
    EXPECT_EQ(Time::inMSecs(199), loop.sleepTime());

    loop.resetIterations(Time::inMSecs(198));
    EXPECT_EQ(Time::inMSecs(-1), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(198)));
    EXPECT_EQ(Time::inMSecs(199), loop.sleepTime());

    loop.resetIterations(Time::inMSecs(199));
    EXPECT_EQ(Time::inMSecs(199), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(199)));
    EXPECT_EQ(Time::inMSecs(399), loop.sleepTime());

    loop.resetIterations(Time::inMSecs(200));
    EXPECT_EQ(Time::inMSecs(199), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(200)));
    EXPECT_EQ(Time::inMSecs(399), loop.sleepTime());
  }
}

TEST(TimedLoopTest, loop) {
  {
    TimedLoop loop(Time::inMSecs(200), Time::inMSecs(199));
    loop.resetIterations(Time::ZERO);
    EXPECT_EQ(1, loop.loop(Time::ZERO));
    EXPECT_EQ(Time::inMSecs(199), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(200)));
    EXPECT_EQ(Time::inMSecs(399), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(Time::inMSecs(200)));
    EXPECT_EQ(Time::inMSecs(399), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(Time::inMSecs(201)));
    EXPECT_EQ(Time::inMSecs(399), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(Time::inMSecs(398)));
    EXPECT_EQ(Time::inMSecs(399), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(399)));
    EXPECT_EQ(Time::inMSecs(599), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(600)));
    EXPECT_EQ(Time::inMSecs(799), loop.sleepTime());
    EXPECT_EQ(3, loop.loop(Time::inMSecs(1200)));
    EXPECT_EQ(Time::inMSecs(1399), loop.sleepTime());
  }
  {
    TimedLoop loop(Time::inMSecs(50), Time::inMSecs(1));
    loop.resetIterations(Time::ZERO);
    EXPECT_EQ(1, loop.loop(Time::ZERO));
    EXPECT_EQ(Time::inMSecs(1), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(50)));
    EXPECT_EQ(Time::inMSecs(51), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(Time::inMSecs(50)));
    EXPECT_EQ(Time::inMSecs(51), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(53)));
    EXPECT_EQ(Time::inMSecs(101), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(Time::inMSecs(98)));
    EXPECT_EQ(Time::inMSecs(101), loop.sleepTime());
    EXPECT_EQ(0, loop.loop(Time::inMSecs(100)));
    EXPECT_EQ(Time::inMSecs(101), loop.sleepTime());
    EXPECT_EQ(1, loop.loop(Time::inMSecs(101)));
    EXPECT_EQ(Time::inMSecs(151), loop.sleepTime());
  }
}

}  // namespace testing
}  // namespace time
}  // namespace controve

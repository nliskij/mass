#include "controve/common/time.hpp"

#include <thread>

#include "gtest/gtest.h"

namespace controve {
namespace time {
namespace testing {

TEST(TimeTest, timespec) {
  timespec start{1234, 9876};
  Time time(start);
  EXPECT_EQ(start.tv_sec, static_cast<time_t>(time.sec()));
  EXPECT_EQ(start.tv_nsec, time.nsec());
  timespec end = time.toTimespec();
  EXPECT_EQ(start.tv_sec, end.tv_sec);
  EXPECT_EQ(start.tv_nsec, end.tv_nsec);
}

TEST(TimeTest, Addition) {
  Time t(42, 100);
  EXPECT_EQ(Time(42, 3100), t + Time(0, 3000));
  EXPECT_EQ(Time(44, 100), t + Time(2, 0));
  EXPECT_EQ(Time(45, 200), t + Time(3, 100));
  EXPECT_EQ(Time(38, 50), t + Time(-5, Time::NSEC_IN_SEC - 50));
  EXPECT_EQ(Time(-42, 100), t + Time(-84, 0));
  EXPECT_EQ(Time(-59, Time::NSEC_IN_SEC - 20),
      Time(-101, Time::NSEC_IN_SEC - 120) + t);
}

TEST(TimeTest, Subtraction) {
  Time t(36, 700);
  EXPECT_EQ(Time(36, 500), t - Time(0, 200));
  EXPECT_EQ(Time(24, 700), t - Time(12, 0));
  EXPECT_EQ(Time(32, 500), t - Time(4, 200));
  EXPECT_EQ(Time(35, 900),
      t - Time(0, Time::NSEC_IN_SEC - 200));
  EXPECT_EQ(Time(37, 900),
      t - Time(-2, Time::NSEC_IN_SEC - 200));
  EXPECT_EQ(Time(36, 7700), t - Time(-1, Time::NSEC_IN_SEC - 7000));
  EXPECT_EQ(Time(-30, Time::NSEC_IN_SEC - 300),
      Time(7, 400) - t);
  EXPECT_EQ(Time(35, Time::NSEC_IN_SEC - 400), t - Time(0, 1100));
}

TEST(TimeTest, Multiplication) {
  Time t(54, Time::NSEC_IN_SEC / 3);
  EXPECT_EQ(Time(108, Time::NSEC_IN_SEC / 3 * 2), t * 2);
  EXPECT_EQ(Time(271, Time::NSEC_IN_SEC / 3 * 2 - 1), t * 5);
  EXPECT_EQ(Time(-109, Time::NSEC_IN_SEC / 3 + 1), t * -2);
  EXPECT_EQ(Time(-55, Time::NSEC_IN_SEC / 3 * 2 + 1), t * - 1);
  EXPECT_EQ(Time(-218, Time::NSEC_IN_SEC / 3 * 2 + 2), (t * -1) * 4);
}

TEST(TimeTest, DivisionByInt) {
  EXPECT_EQ(Time(5, Time::NSEC_IN_SEC / 10 * 4 + 50), Time(54, 500) / 10);
  EXPECT_EQ(Time(2, Time::NSEC_IN_SEC / 4 * 3),
      Time(5, Time::NSEC_IN_SEC / 2) / 2);
  EXPECT_EQ(Time(-3, Time::NSEC_IN_SEC / 4 * 3),
      Time(-5, Time::NSEC_IN_SEC / 2) / 2);
}

TEST(TimeTest, DivisionByTime) {
  EXPECT_DOUBLE_EQ(2, Time(10, 0) / Time(5, 0));
  EXPECT_DOUBLE_EQ(9, Time(27, 0) / Time(3, 0));
  EXPECT_DOUBLE_EQ(9.25, Time(37, 0) / Time(4, 0));
  EXPECT_DOUBLE_EQ(5.25, Time(36, Time::NSEC_IN_SEC / 4 * 3) / Time(7, 0));
  EXPECT_DOUBLE_EQ(-5.25, Time(-37, Time::NSEC_IN_SEC / 4) / Time(7, 0));
  EXPECT_DOUBLE_EQ(-5.25, Time(36, Time::NSEC_IN_SEC / 4 * 3) / Time(-7, 0));
}

TEST(TimeTest, Negation) {
  EXPECT_EQ(Time(-4, 30000), -Time(3, Time::NSEC_IN_SEC - 30000));
  EXPECT_EQ(Time(5, Time::NSEC_IN_SEC * 2 / 3 + 1), -Time(-6, Time::NSEC_IN_SEC / 3));
}

TEST(TimeTest, Comparisons) {
  EXPECT_TRUE(Time(4, 100) > Time(4, 99));
  EXPECT_TRUE(Time(4, 100) >= Time(4, 99));
  EXPECT_TRUE(Time(4, 100) < Time(4, 101));
  EXPECT_TRUE(Time(4, 100) <= Time(4, 101));
  EXPECT_TRUE(Time(4, 100) >= Time(4, 100));
  EXPECT_TRUE(Time(4, 100) <= Time(4, 100));
  EXPECT_TRUE(Time(4, 100) <= Time(5, 100));
  EXPECT_TRUE(Time(5, 100) >= Time(4, 100));

  EXPECT_TRUE(Time(-4, 100) > Time(-4, 99));
  EXPECT_TRUE(Time(-4, 100) >= Time(-4, 99));
  EXPECT_TRUE(Time(-4, 100) < Time(-4, 101));
  EXPECT_TRUE(Time(-4, 100) <= Time(-4, 101));
  EXPECT_TRUE(Time(-4, 100) >= Time(-4, 100));
  EXPECT_TRUE(Time(-4, 100) <= Time(-4, 100));
  EXPECT_TRUE(Time(-4, 100) >= Time(-5, 100));
  EXPECT_TRUE(Time(-5, 100) <= Time(-4, 100));
}

TEST(TimeTest, Modulus) {
  EXPECT_EQ(Time(0, Time::NSEC_IN_SEC / 10 * 2),
      Time(50, 0) % (Time::NSEC_IN_SEC / 10 * 3));
  EXPECT_EQ(Time(-1, Time::NSEC_IN_SEC / 10 * 8),
      Time(-50, 0) % (Time::NSEC_IN_SEC / 10 * 3));
  EXPECT_EQ(Time(-1, Time::NSEC_IN_SEC / 10 * 8),
      Time(-50, 0) % (-Time::NSEC_IN_SEC / 10 * 3));
  EXPECT_EQ(Time(0, Time::NSEC_IN_SEC / 10 * 2),
      Time(50, 0) % (-Time::NSEC_IN_SEC / 10 * 3));
  EXPECT_EQ(Time(1, Time::NSEC_IN_SEC / 10),
      Time(60, Time::NSEC_IN_SEC / 10) % (Time::NSEC_IN_SEC / 10 * 12));
}

TEST(TimeTest, InSeconds) {
  EXPECT_EQ(Time(2, Time::NSEC_IN_SEC / 100 * 55 - 1),
    Time::inSeconds(2.55));
  EXPECT_EQ(Time(-3, Time::NSEC_IN_SEC / 100 * 45),
    Time::inSeconds(-2.55));
}

TEST(TimeTest, ToSeconds) {
  EXPECT_DOUBLE_EQ(13.23, Time::inSeconds(13.23).toSeconds());
  EXPECT_NEAR(-13.23, Time::inSeconds(-13.23).toSeconds(),
      1.0 / Time::NSEC_IN_SEC * 2);
}

TEST(TimeTest, inMSecs) {
  Time t = Time::inMSecs(263210);
  EXPECT_EQ(263, t.sec());
  EXPECT_EQ(210000000, t.nsec());

  Time t2 = Time::inMSecs(-263210);
  EXPECT_EQ(-264, t2.sec());
  EXPECT_EQ(Time::NSEC_IN_SEC - 210000000, t2.nsec());
}

TEST(TimeTest, toMSecs) {
  EXPECT_EQ(210730, Time(210, 730000000).toMSecs());
  EXPECT_EQ(-210730, Time(-211, Time::NSEC_IN_SEC - 730000000).toMSecs());
}

TEST(TimeTest, inNSecs) {
  Time t = Time::inNSecs(static_cast<int64_t>(116696662909ll));
  EXPECT_EQ(116, t.sec());
  EXPECT_EQ(696662909, t.nsec());

  Time t2 = Time::inNSecs(static_cast<int64_t>(-116696662909ll));
  EXPECT_EQ(-117, t2.sec());
  EXPECT_EQ(Time::NSEC_IN_SEC - 696662909, t2.nsec());
}

TEST(TimeTest, inUSecs) {
  Time t = Time::inUSecs(669666290);
  EXPECT_EQ(669, t.sec());
  EXPECT_EQ(666290000, t.nsec());

  Time t2 = Time::inUSecs(-669666290);
  EXPECT_EQ(-670, t2.sec());
  EXPECT_EQ(Time::NSEC_IN_SEC - 666290000, t2.nsec());
}

TEST(TimeTest, toUSecs) {
  EXPECT_EQ(669000666, Time(669, 666000).toUSecs());
  EXPECT_EQ(-669000666, Time(-670, Time::NSEC_IN_SEC - 666000).toUSecs());
}

TEST(TimeTest, Abs) {
  EXPECT_EQ(Time(100, 4242), Time(100, 4242).abs());
  EXPECT_EQ(Time(222, Time::NSEC_IN_SEC * 0.4),
    Time(-223, Time::NSEC_IN_SEC * 0.6).abs());
  EXPECT_EQ(-Time(-222, 224).toNSecs(),
      Time(221, Time::NSEC_IN_SEC - 224).toNSecs());
}

TEST(TimeTest, fromRate) {
  EXPECT_EQ(Time(0, Time::NSEC_IN_SEC / 100), Time::fromRate(100));
}

TEST(TimeTest, NowSleepFor) {
  sleepFor(Time(0, Time::NSEC_IN_SEC / 10));
  Time start = Time::now();
  static constexpr Time sleepTime = Time(0, Time::NSEC_IN_SEC * 2 / 10);
  sleepFor(sleepTime);
  Time difference = Time::now() - start;
  EXPECT_GE(difference, sleepTime);
  EXPECT_LT(difference, sleepTime + Time(0, Time::NSEC_IN_SEC / 100));
}

}  // testing
}  // time
}  // controve

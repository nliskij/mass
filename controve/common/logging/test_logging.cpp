#include <string>

#include "controve/common/logging/logging.hpp"

#include "gtest/gtest.h"

void doLog(log_level level, const char *format, ...) {
  printf("%d: %s\n", level, format);
}

namespace controve {
namespace testing {

TEST(LoggingTest, Base) {
  ::testing::internal::CaptureStdout();
  LOG(INFO, "Test");
  std::string output = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "1: controve/common/logging/test_logging.cpp: 16: %s: Test\n");
}

// note that the predicate will be filled if it fails (properly) in doLog
TEST(LoggingDeathTest, FATAL) {
  EXPECT_EXIT(LOG(FATAL, "Test"), ::testing::KilledBySignal(SIGABRT),
      "");
}

}  // namespace testing
}  // namespace controve

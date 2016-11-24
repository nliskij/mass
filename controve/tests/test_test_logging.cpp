#include "controve/tests/test_logging.hpp"

#include <thread>

#include "gtest/gtest.h"

#include "controve/common/logging/logging.hpp"

namespace controve {
namespace testing {

TEST(TestLoggingQueue, Multithreading) {
  enableTestLogging();

  ::std::thread thread([]() {
      for (int i = 0; i < 1000; ++i) {
        LOG(INFO, "test from thread\n");
      }
  });
  for (int i = 0; i < 1000; ++i) {
    LOG(INFO, "not from thread\n");
  }
  thread.join();
}

}  // namespace testing
}  // namespace controve

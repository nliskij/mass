#include "controve/common/die.hpp"

#include "gtest/gtest.h"

namespace controve {
namespace testing {

TEST(DieTest, Working) {
  EXPECT_EXIT(die("str=%s num=%d\n", "test", 9),
      ::testing::KilledBySignal(SIGABRT), ".*str=test num=9\n");
}

}  // namespace testing
}  // namespace controve

#include "controve/common/strerror.hpp"

#include <cerrno>

#include "gtest/gtest.h"

namespace controve {
namespace testing {

TEST(StrerrorTest, Basic) {
  EXPECT_STREQ("Argument list too long", controve::controve_strerror(E2BIG));
  EXPECT_STREQ("Bad file descriptor", controve::controve_strerror(EBADF));
  EXPECT_STREQ("Unknown error 4021", controve::controve_strerror(4021));
}

// Compare every single error number with the output of the system strerror
// function.
TEST(StrerrorTest, All) {
  for (int i = 0; i < 4095; ++i) {
    SCOPED_TRACE("iteration " + ::std::to_string(i));
    EXPECT_STREQ(strerror(i), controve_strerror(i));
  }
}

}
}

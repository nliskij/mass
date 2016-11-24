#include <iostream>
#include <getopt.h>

#include "gtest/gtest.h"

///
/// @file test_main.cpp
///
/// @brief A wrapper around the googletest library to allow for commandline
/// options to be passed in for our libraries in a uniform manner.
///
/// By adding commandline options to this file we can generalize the setup of
/// our tests by using this file instead of including googletest itself.
///
/// @author Lee Mracek
///
/// @bug No known bugs

namespace controve {
namespace testing {

void setFileName(const char *filename) __attribute__((weak));
void forcePrintLogsDuringTests() __attribute__((weak));

}  // namespace testing
}  // namespace controve

/// @brief A wrapper main for our test cases.
GTEST_API_ int main(int argc, char **argv) {
  static const struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"print-logs", no_argument, 0, 'p'},
    {"log-file", required_argument, 0, 'o'},
    {0, 0, 0, 0},
  };
    
  testing::InitGoogleTest(&argc, argv);


  while (true) {
    int c = getopt_long(argc, argv, "pho:", long_options, nullptr);

    if (c == -1) {
      break;
    }

    switch (c) {
      case 'h':
        printf(
            "\nTest options:\n"
            "  -p, --print-logs\n"
            "      Print the log messages as they are being generated.\n"
            "  -o, --log-file=FILE\n"
            "      Print all log messages to FILE instead of standard output\n"
            );
        break;

      case 'p':
        if (::controve::testing::forcePrintLogsDuringTests) {
          ::controve::testing::forcePrintLogsDuringTests();
        }
        break;

      case 'o':
        if (::controve::testing::setFileName) {
          ::controve::testing::setFileName(optarg);
        }
        break;

      case '?':
        abort();
    }
  }

  return RUN_ALL_TESTS();
}

#include <iostream>

#include "gtest/gtest.h"

/**
 * @file test_main.cpp
 *
 * @brief A wrapper around the googletest library to allow for commandline
 * options to be passed in for our libraries in a uniform manner.
 *
 * By adding commandline options to this file we can generalize the setup of
 * our tests by using this file instead of including googletest itself.
 *
 * @author Lee Mracek
 *
 * @bug No known bugs
 */

/// @brief A wrapper main for our test cases.
GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    // put any command line options here

    return RUN_ALL_TESTS();
}

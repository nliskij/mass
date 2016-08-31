cc_library(
    name = 'timed_loop',
    visibility = [ '//visibility:public' ],
    srcs = [ 'timed_loop.cpp' ],
    hdrs = [ 'timed_loop.hpp' ],
    deps = [
        '//controve/common:time',
    ],
)

cc_test(
    name = 'test_timed_loop',
    srcs = [ 'test_timed_loop.cpp' ],
    deps = [
        '//controve/common/threading:timed_loop',
        '//controve/tests:googletest',
    ],
    size = 'small',
)

cc_library(
    name = 'macros',
    visibility = ['//visibility:public'],
    hdrs = [ 'macros.hpp' ],
)

cc_library(
    name = 'time',
    visibility = [ '//visibility:public' ],
    srcs = [ 'time.cpp' ],
    hdrs = [ 'time.hpp' ],
)

cc_test(
    name = 'test_time',
    srcs = [ 'test_time.cpp' ],
    size = 'small',
    deps = [
        ':time',
        '//controve/tests:googletest',
    ],
)

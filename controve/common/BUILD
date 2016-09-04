cc_library(
    name = 'macros',
    visibility = ['//visibility:public'],
    hdrs = [ 'macros.hpp' ],
)

cc_library(
    name = 'strerror',
    visibility = ['//visibility:public'],
    srcs = [ 'strerror.cpp' ],
    hdrs = [ 'strerror.hpp' ],
)

cc_test(
    name = 'test_strerror',
    srcs = [ 'test_strerror.cpp' ],
    size = 'small',
    deps = [
        ':strerror',
        '//controve/tests:googletest',
    ],
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

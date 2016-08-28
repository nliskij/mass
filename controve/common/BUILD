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

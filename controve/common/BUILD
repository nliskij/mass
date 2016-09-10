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

cc_library(
    name = 'config',
    visibility = ['//visibility:public'],
    hdrs = [ 'config.hpp' ],
)

cc_library(
    name = 'die',
    visibility = ['//visibility:public'],
    srcs = [
        'die.cpp',
    ],
    hdrs = [
        'die.hpp',
    ],
    deps = [
        '//controve/common:config',
        '//controve/common/libc:strerror',
    ],
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

cc_test(
    name = 'test_die',
    srcs = [ 'test_die.cpp' ],
    size = 'small',
    deps = [
        ':die',
        '//controve/tests:googletest',
    ],
)

cc_library(
    name = 'googletest',
    visibility = ['//visibility:public'],
    srcs = [
       'test_main.cpp',
    ],
    deps = [
        '//external:googletest',
    ],
    testonly = True,
)

cc_library(
    name = 'test_logging',
    visibility = ['//visibility:public'],
    srcs = [
      'test_logging.cpp',
    ],
    hdrs = [
      'test_logging.hpp',
    ],
    deps = [
      ':googletest',
      '//controve/common/logging:handlers',
    ],
    testonly = True,
)

cc_test(
  name = 'test_test_logging',
  srcs = [
    'test_test_logging.cpp',
  ],
  deps = [
    ':googletest',
    ':test_logging',
    '//controve/common/logging:logging',
  ],
)

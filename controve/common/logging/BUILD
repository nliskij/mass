cc_library(
  name = 'logging',
  visibility = ['//visibility:public'],
  hdrs = [
    'logging.hpp',
  ],
  deps = [
    '//controve/common:die',
    '//controve/common/libc:strerror',
    '//controve/common:config'
  ]
)

cc_test(
  name = 'test_logging',
  srcs = [
    'test_logging.cpp',
  ],
  deps = [
    '//controve/tests:googletest',
    ':logging',
  ]
)

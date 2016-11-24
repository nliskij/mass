cc_library(
  name = 'logging',
  visibility = ['//visibility:public'],
  hdrs = [
    'logging.hpp',
    'frame.hpp',
  ],
  srcs = [
    'interface.cpp',
    'frame.cpp'
  ],
  deps = [
    '//controve/common:die',
    '//controve/common/libc:strerror',
    '//controve/common:config'
  ]
)

cc_library(
  name = 'handlers',
  visibility = ['//visibility:public'],
  srcs = [
    'handlers.cpp',
  ],
  hdrs = [
    'handlers.hpp',
  ],
  deps = [
    '//controve/common:die',
    ':logging',
    '//controve/common:config',
  ]
)

cc_test(
  name = 'test_handlers',
  srcs = [
    'test_handlers.cpp',
  ],
  deps = [
    '//controve/tests:googletest',
    ':logging',
    ':handlers',
  ],
)

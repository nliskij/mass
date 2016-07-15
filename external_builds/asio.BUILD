cc_library(
  name = 'asio',
  visibility = ['//visibility:public'],
  includes = ['asio/include'],
  hdrs = glob(['asio/include/*'], exclude = [
    'asio/include/asio/detail/config.hpp',
  ]),
  defines = [
    'ASIO_STANDALONE',
  ],
)

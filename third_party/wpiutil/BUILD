licenses(['notice'])

cc_library(
  name = 'wpiutil',
  visibility = ['//visibility:public'],
  srcs = glob([
    'src/**/*.cpp',
    'src/**/*.h',
  ]),
  copts = [ '-Wno-cast-align',
    '-Wno-unused-parameter',
  ],
  hdrs = glob([
    'include/**/*.h',
  ]),
  includes = [
    'include',
  ],
  linkopts = [
    '-lpthread',
  ],
)

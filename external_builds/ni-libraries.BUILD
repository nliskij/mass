cc_library(
  name = 'ni-libraries',
  visibility = ['//visibility:public'],
  hdrs = glob(['include/**/*.h']),
  includes = ['include'],
  srcs = [
    'lib/libFRC_NetworkCommunication.so.17.0.0',
    'lib/libRoboRIO_FRC_ChipObject.so.17.0.0',
    'lib/libNiFpgaLv.so.16.0.0',
    'lib/libNiFpga.so.16.0.0',
    'lib/libNiRioSrv.so.16.0.0',
    'lib/libspi.so.1.0.0',
    'lib/libi2c.so.2.0.0',
  ],
  linkstatic = True,
)

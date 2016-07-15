licenses(['notice'])

cc_library(
  name = 'eigen',
  visibility = ['//visibility:public'],
  srcs = glob(['Eigen/src/**/*.h']),
  includes = ['.'],
  hdrs = glob(['Eigen/*'], [
    'Eigen/CholmodSupport',
    'Eigen/MetisSupport',
    'Eigen/PaStiXSupport',
    'Eigen/PardisoSupport',
    'Eigen/SPQRSupport',
    'Eigen/UmfPackSupport',
  ]),
)

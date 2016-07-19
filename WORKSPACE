new_local_repository(
    name = 'usr_repo',
    path = '/usr',
    build_file = 'external_builds/usr.BUILD',
)

new_http_archive(
    name = 'allwpilib_ni_libraries_repo',
    build_file = 'external_builds/ni-libraries.BUILD',
    sha256 = 'c639f39bdf97f12b2d13b6194cf3efa4dde8ef0e4c127672d8c2634963dcf860', 
    url = 'https://valkyrierobotics.com/builddeps/all_ni-libraries_083362b.tar.gz',
    strip_prefix = 'ni-libraries',
)

bind(
    name = 'ni-libraries',
    actual = '@allwpilib_ni_libraries_repo//:ni-libraries',
)

new_git_repository(
    name = 'slycot_repo',
    remote = 'https://github.com/avventi/Slycot.git',
    build_file = 'external_builds/slycot.BUILD',
    commit = '5af5f283cb23cbe23c4dfea4d5e56071bdbd6e70',
)

bind(
    name = 'slycot',
    actual = '@slycot_repo//:slycot',
)

new_git_repository(
    name = 'python_gflags_repo',
    remote = 'https://github.com/gflags/python-gflags.git',
    build_file = 'external_builds/gflags.BUILD',
    commit = '41c4571864f0db5823e07715317e7388e94faabc',
)

bind(
    name = 'python-gflags',
    actual = '@python_gflags_repo//:gflags',
)

new_http_archive(
    name = 'python_glog_repo',
    build_file = 'external_builds/glog.BUILD',
    sha256 = '953fd80122c48023d1148e6d1bda2763fcab59c8a81682bb298238a5935547b0',
    url = 'https://pypi.python.org/packages/source/g/glog/glog-0.1.tar.gz',
    strip_prefix = 'glog-0.1',
)

bind(
    name = 'python-glog',
    actual = '@python_glog_repo//:glog',
)

new_git_repository(
    name = 'googletest_repo',
    remote = 'https://github.com/google/googletest',
    build_file = 'external_builds/googletest.BUILD',
    commit = 'ec44c6c1675c25b9827aacd08c02433cccde7780',
)

bind(
    name = 'googletest',
    actual = '@googletest_repo//:googletest',
)

new_http_archive(
    name = 'eigen_repo',
    build_file = 'external_builds/eigen.BUILD',
    sha256 = '8d01d2d3a173c59065642a08d1dd661b399e4fed6edbda632143e7be937de7e0',
    url = 'https://valkyrierobotics.com/builddeps/eigen-eigen-07105f7124f9.tar.gz',
    strip_prefix = 'eigen-eigen-07105f7124f9',
)

new_http_archive(
    name = 'arm_frc_linux_gnueabi_repo',
    build_file = 'tools/cpp/arm-frc-linux-gnueabi/arm-frc-linux-gnueabi.BUILD',
    sha256 = '9e93b0712e90d11895444f720f0c90c649fb9becb4ca28bb50749d9074eb1306',
    url = 'http://frc971.org/Build-Dependencies/roborio-compiler-2016.tar.gz',
)

new_http_archive(
  name = 'linaro_linux_gcc_4_9_repo',
  build_file = 'tools/cpp/linaro_linux_gcc/linaro_linux_gcc_4.9.BUILD',
  sha256 = '25e97bcb0af4fd7cd626d5bb1b303c7d2cb13acf2474e335e3d431d1a53fbb52',
  url = 'http://frc971.org/Build-Dependencies/gcc-linaro-4.9-2015.05-x86_64_arm-linux-gnueabihf.tar.gz',
)

new_git_repository(
  name = 'asio_repo',
  build_file = 'external_builds/asio.BUILD',
  remote = 'https://github.com/chriskohlhoff/asio',
  commit = '722f7e2be05a51c69644662ec514d6149b2b7ef8',
)

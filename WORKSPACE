new_local_repository(
    name = 'usr_repo',
    path = '/usr',
    build_file = 'external_builds/usr.BUILD',
)

new_http_archive(
    name = 'allwpilib_ni_libraries_repo',
    build_file = 'external_builds/ni-libraries.BUILD',
    sha256 = '853448bd5e5a3e222f779d4b41984eeb334a259a47c70013b39545a01417c244',
    url = 'https://valkyrierobotics.com/builddeps/all_ni-libraries_bc7ab17.tar.gz',
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

#bind(
#    name = 'googletest',
#    actual = '@googletest_repo//:googletest',
#)

new_http_archive(
    name = 'eigen_repo',
    build_file = 'external_builds/eigen.BUILD',
    sha256 = '8d01d2d3a173c59065642a08d1dd661b399e4fed6edbda632143e7be937de7e0',
    url = 'https://valkyrierobotics.com/builddeps/eigen-eigen-26667be4f70b.tar.gz',
    strip_prefix = 'eigen-eigen-26667be4f70b.tar.gz',
)

new_http_archive(
    name = 'arm_frc_linux_gnueabi_repo',
    build_file = 'tools/cpp/arm-frc-linux-gnueabi/arm-frc-linux-gnueabi.BUILD',
    sha256 = '9e93b0712e90d11895444f720f0c90c649fb9becb4ca28bb50749d9074eb1306',
    url = 'https://valkyrierobotics.com/builddeps/roborio-compiler-2016.tar.gz',
)

new_http_archive(
  name = 'linaro_linux_gcc_4_9_repo',
  build_file = 'tools/cpp/linaro_linux_gcc/linaro_linux_gcc_4.9.BUILD',
  sha256 = '25e97bcb0af4fd7cd626d5bb1b303c7d2cb13acf2474e335e3d431d1a53fbb52',
  url = 'https://valkyrierobotics.com/builddeps/gcc-linaro-4.9-2015.05-x86_64_arm-linux-gnueabihf.tar.gz',
)

new_git_repository(
  name = 'asio_repo',
  build_file = 'external_builds/asio.BUILD',
  remote = 'https://github.com/chriskohlhoff/asio',
  commit = '722f7e2be05a51c69644662ec514d6149b2b7ef8',
)

new_http_archive(
  name = 'six_repo',
  build_file = 'external_builds/six.BUILD',
  url = 'https://pypi.python.org/packages/source/s/six/six-1.10.0.tar.gz',
  strip_prefix = 'six-1.10.0',
  sha256 = '105f8d68616f8248e24bf0e9372ef04d3cc10104f1980f54d57b2ce73a5ad56a',
)

# In for protobuf. Don't use these, that use is unsupported.
bind(
  name = 'six',
  actual = '@six_repo//:six',
)

bind(
    name = 'gtest',
    actual = '@googletest_repo//:googlemock',
)

bind(
    name = 'gtest_main',
    actual = '@googletest_repo//:googlemock_main',
)

# TODO(m3rcuriel) remember to probably replace this with actual python headers
# for if we ever use python protobuf
bind(
  name = 'python_headers',
  actual = '//:dummy',
)

#=======================================================#
######################## BOOST ##########################
#=======================================================#

new_git_repository(
	name = "algorithm_repo",
	remote = "https://github.com/boostorg/algorithm",
	commit = "f6d20e612bf076e6d7e3ce04c6308076acd7f772",
	build_file = "external_builds/boost/algorithm.BUILD",
)

bind(
    name = "boost_algorithm",
    actual = "@algorithm_repo//:algorithm",
)

new_git_repository(
	name = "align_repo",
	remote = "https://github.com/boostorg/align",
	commit = "9fa8e7e5c1bf0a7798b6f796c7f1be4c9d05f991",
	build_file = "external_builds/boost/align.BUILD",
)

bind(
    name = "boost_align",
    actual = "@align_repo//:align",
)

new_git_repository(
    name = "array_repo",
    remote = "https://github.com/boostorg/array",
    commit = "0d4fa276f4bce35572a4027f3cd3cd0edd502162",
    build_file = "external_builds/boost/array.BUILD",
)

bind(
    name = "boost_array",
    actual = "@array_repo//:array",
)

new_git_repository(
    name = "boost_asio_repo",
    remote = "https://github.com/boostorg/asio",
    commit = "f687d8690234f56d1e5d3a6a057f1958903fd1d0",
    build_file = "external_builds/boost/asio.BUILD",
)

bind(
    name = "boost_asio",
    actual = "@boost_asio_repo//:asio"
)

new_git_repository(
	name = "assert_repo",
	remote = "https://github.com/boostorg/assert",
	commit = "938bfbb080b820d9d63f8b0cdf9fe18542dd1329",
	build_file = "external_builds/boost/assert.BUILD",
)

bind(
    name = "boost_assert",
    actual = "@assert_repo//:assert",
)

new_git_repository(
	name = "atomic_repo",
	remote = "https://github.com/boostorg/atomic",
	commit = "ffe7710a90b347ced6dc1341bab57f7fc01385a8",
	build_file = "external_builds/boost/atomic.BUILD",
)

bind(
    name = "boost_atomic",
    actual = "@atomic_repo//:atomic",
)

new_git_repository(
	name = "bind_repo",
	remote = "https://github.com/boostorg/bind",
	commit = "2821b51a50db59415e883b960718f0c629e7ac2b",
	build_file = "external_builds/boost/bind.BUILD",
)

bind(
    name = "boost_bind",
    actual = "@bind_repo//:bind",
)

new_git_repository(
	name = "algorithm_repo",
	remote = "https://github.com/boostorg/algorithm",
	commit = "f6d20e612bf076e6d7e3ce04c6308076acd7f772",
	build_file = "external_builds/boost/algorithm.BUILD",
)

bind(
    name = "boost_algorithm",
    actual = "@algorithm_repo//:algorithm",
)

new_git_repository(
	name = "align_repo",
	remote = "https://github.com/boostorg/align",
	commit = "9fa8e7e5c1bf0a7798b6f796c7f1be4c9d05f991",
	build_file = "external_builds/boost/align.BUILD",
)

bind(
    name = "boost_align",
    actual = "@align_repo//:align",
)

new_git_repository(
	name = "assert_repo",
	remote = "https://github.com/boostorg/assert",
	commit = "938bfbb080b820d9d63f8b0cdf9fe18542dd1329",
	build_file = "external_builds/boost/assert.BUILD",
)

bind(
    name = "boost_assert",
    actual = "@assert_repo//:assert",
)

new_git_repository(
	name = "atomic_repo",
	remote = "https://github.com/boostorg/atomic",
	commit = "ffe7710a90b347ced6dc1341bab57f7fc01385a8",
	build_file = "external_builds/boost/atomic.BUILD",
)

bind(
    name = "boost_atomic",
    actual = "@atomic_repo//:atomic",
)

new_git_repository(
	name = "bind_repo",
	remote = "https://github.com/boostorg/bind",
	commit = "2821b51a50db59415e883b960718f0c629e7ac2b",
	build_file = "external_builds/boost/bind.BUILD",
)

bind(
    name = "boost_bind",
    actual = "@bind_repo//:bind",
)

new_git_repository(
	name = "chrono_repo",
	remote = "https://github.com/boostorg/chrono",
	commit = "4001d9cbeea9ea06ebc6daa8f9f5ba5290ef4284",
	build_file = "external_builds/boost/chrono.BUILD",
)

bind(
    name = "boost_chrono",
    actual = "@chrono_repo//:chrono",
)

new_git_repository(
	name = "concept_check_repo",
	remote = "https://github.com/boostorg/concept_check",
	commit = "c7d61df2af0bdc83b8654d4c63fa16307f9d34f3",
	build_file = "external_builds/boost/concept_check.BUILD",
)

bind(
    name = "boost_concept_check",
    actual = "@concept_check_repo//:concept_check",
)

new_git_repository(
	name = "config_repo",
	remote = "https://github.com/boostorg/config",
	commit = "65fa2a46f2d87d404d2105b8e24c9f258c611669",
	build_file = "external_builds/boost/config.BUILD",
)

bind(
    name = "boost_config",
    actual = "@config_repo//:config",
)

new_git_repository(
	name = "container_repo",
	remote = "https://github.com/boostorg/container",
	commit = "7e232bbc1979aafce52f720095e894f138362e1f",
	build_file = "external_builds/boost/container.BUILD",
)

bind(
    name = "boost_container",
    actual = "@container_repo//:container",
)

new_git_repository(
	name = "core_repo",
	remote = "https://github.com/boostorg/core",
	commit = "df2f358766ddc0773f185e1f1dfdde61eb920eb5",
	build_file = "external_builds/boost/core.BUILD",
)

bind(
    name = "boost_core",
    actual = "@core_repo//:core",
)

new_git_repository(
	name = "date_time_repo",
	remote = "https://github.com/boostorg/date_time",
	commit = "6015e3039114c0f2ba456e00dd50404e3fb88275",
	build_file = "external_builds/boost/date_time.BUILD",
)

bind(
    name = "boost_date_time",
    actual = "@date_time_repo//:date_time",
)

new_git_repository(
	name = "detail_repo",
	remote = "https://github.com/boostorg/detail",
	commit = "6abcc6cd09f7ef19bf1039c91fdbd8842b729785",
	build_file = "external_builds/boost/detail.BUILD",
)

bind(
    name = "boost_detail",
    actual = "@detail_repo//:detail",
)

new_git_repository(
	name = "exception_repo",
	remote = "https://github.com/boostorg/exception",
	commit = "c1e22846281c3b6d9d52b7a17866fdf7c9973178",
	build_file = "external_builds/boost/exception.BUILD",
)

bind(
    name = "boost_exception",
    actual = "@exception_repo//:exception",
)

new_git_repository(
	name = "filesystem_repo",
	remote = "https://github.com/boostorg/filesystem",
	commit = "65a27cc520cea5aa9dd65d7b756a804d3cf8e14c",
	build_file = "external_builds/boost/filesystem.BUILD",
)

bind(
    name = "boost_filesystem",
    actual = "@filesystem_repo//:filesystem",
)

new_git_repository(
	name = "foreach_repo",
	remote = "https://github.com/boostorg/foreach",
	commit = "68645f9c47d215bda75e8ffec46b215e6de7f031",
	build_file = "external_builds/boost/foreach.BUILD",
)

bind(
    name = "boost_foreach",
    actual = "@foreach_repo//:foreach",
)

new_git_repository(
	name = "function_repo",
	remote = "https://github.com/boostorg/function",
	commit = "fed32bc072195d24e70fc0835fda9a55128bab74",
	build_file = "external_builds/boost/function.BUILD",
)

bind(
    name = "boost_function",
    actual = "@function_repo//:function",
)

new_git_repository(
	name = "function_types_repo",
	remote = "https://github.com/boostorg/function_types",
	commit = "290a8e88e7536352008373aa59a5508aadcbfd75",
	build_file = "external_builds/boost/function_types.BUILD",
)

bind(
    name = "boost_function_types",
    actual = "@function_types_repo//:function_types",
)

new_git_repository(
	name = "functional_repo",
	remote = "https://github.com/boostorg/functional",
	commit = "815fc115a0e9b20327f9b10d1cd3c07c90c9e670",
	build_file = "external_builds/boost/functional.BUILD",
)

bind(
    name = "boost_functional",
    actual = "@functional_repo//:functional",
)

new_git_repository(
	name = "heap_repo",
	remote = "https://github.com/boostorg/heap",
	commit = "1d6f4c1eb89ce42798dbd45981359e04aa00c781",
	build_file = "external_builds/boost/heap.BUILD",
)

bind(
    name = "boost_heap",
    actual = "@heap_repo//:heap",
)

new_git_repository(
	name = "integer_repo",
	remote = "https://github.com/boostorg/integer",
	commit = "175a1caa584584fbb1ecebcb668f68616bb7aaed",
	build_file = "external_builds/boost/integer.BUILD",
)

bind(
    name = "boost_integer",
    actual = "@integer_repo//:integer",
)

new_git_repository(
	name = "iterator_repo",
	remote = "https://github.com/boostorg/iterator",
	commit = "711a0232f8eba3582264157c09f74839b6c778d2",
	build_file = "external_builds/boost/iterator.BUILD",
)

bind(
    name = "boost_iterator",
    actual = "@iterator_repo//:iterator",
)

new_git_repository(
	name = "intrusive_repo",
	remote = "https://github.com/boostorg/intrusive",
	commit = "4014562502d7a9fb9a13b09a908e0d757e368969",
	build_file = "external_builds/boost/intrusive.BUILD",
)

bind(
    name = "boost_intrusive",
    actual = "@intrusive_repo//:intrusive",
)

new_git_repository(
	name = "io_repo",
	remote = "https://github.com/boostorg/io",
	commit = "b3e349c595fd494e98642eafd6a3534d9f86cbab",
	build_file = "external_builds/boost/io.BUILD",
)

bind(
    name = "boost_io",
    actual = "@io_repo//:io",
)

new_git_repository(
    name = "lexical_cast_repo",
    remote = "https://github.com/boostorg/lexical_cast",
    commit = "0bfc6c2dce0b9068731286a3cb037fc12ac6e130",
    build_file = "external_builds/boost/lexical_cast.BUILD",
)

bind(
    name = "boost_lexical_cast",
    actual = "@lexical_cast_repo//:lexical_cast",
)

new_git_repository(
	name = "math_repo",
	remote = "https://github.com/boostorg/math",
	commit = "2165b95f524d15ddaf9a85fe1767ab0df4e92dd0",
	build_file = "external_builds/boost/math.BUILD",
)

bind(
    name = "boost_math",
    actual = "@math_repo//:math",
)

new_git_repository(
	name = "move_repo",
	remote = "https://github.com/boostorg/move",
	commit = "1194a39ab3195a17c849e1d11f4305ff6727df8b",
	build_file = "external_builds/boost/move.BUILD",
)

bind(
    name = "boost_move",
    actual = "@move_repo//:move",
)

new_git_repository(
	name = "mpl_repo",
	remote = "https://github.com/boostorg/mpl",
	commit = "3b126bdf8c7abbfef27101232a379c8e0c3db1ac",
	build_file = "external_builds/boost/mpl.BUILD",
)

bind(
    name = "boost_mpl",
    actual = "@mpl_repo//:mpl",
)

new_git_repository(
	name = "multi_index_repo",
	remote = "https://github.com/boostorg/multi_index",
	commit = "b4697425472fce11ecbcde67d28e616e29b6752a",
	build_file = "external_builds/boost/multi_index.BUILD",
)

bind(
    name = "boost_multi_index",
    actual = "@multi_index_repo//:multi_index",
)

new_git_repository(
    name = "numeric_conversion_repo",
    remote = "https://github.com/boostorg/numeric_conversion",
    commit = "c9d7a49b4a980754f22a1832a68188f47d1afaae",
    build_file = "external_builds/boost/numeric_conversion.BUILD",
)

bind(
    name = "boost_numeric_conversion",
    actual = "@numeric_conversion_repo//:numeric_conversion",
)

new_git_repository(
	name = "optional_repo",
	remote = "https://github.com/boostorg/optional",
	commit = "b99c1fdcc2b5dd542c71a5ea703ca282f179980b",
	build_file = "external_builds/boost/optional.BUILD",
)

bind(
    name = "boost_optional",
    actual = "@optional_repo//:optional",
)

new_git_repository(
	name = "parameter_repo",
	remote = "https://github.com/boostorg/parameter",
	commit = "6ad2d6b207a98e7d6c0faeab5b423cc7f8fc0c24",
	build_file = "external_builds/boost/parameter.BUILD",
)

bind(
    name = "boost_parameter",
    actual = "@parameter_repo//:parameter",
)

new_git_repository(
	name = "predef_repo",
	remote = "https://github.com/boostorg/predef",
	commit = "347e7dfdc555107bf001a978e8f138e5a16570c6",
	build_file = "external_builds/boost/predef.BUILD",
)

bind(
    name = "boost_predef",
    actual = "@predef_repo//:predef",
)

new_git_repository(
	name = "preprocessor_repo",
	remote = "https://github.com/boostorg/preprocessor",
	commit = "e70abe7b4984119214682caf2a4d21e88a37ab90",
	build_file = "external_builds/boost/preprocessor.BUILD",
)

bind(
    name = "boost_preprocessor",
    actual = "@preprocessor_repo//:preprocessor",
)

new_git_repository(
	name = "range_repo",
	remote = "https://github.com/boostorg/range",
	commit = "5a37aa4e981cd3362975ba22c03558ff23654d47",
	build_file = "external_builds/boost/range.BUILD",
)

bind(
    name = "boost_range",
    actual = "@range_repo//:range",
)

new_git_repository(
	name = "ratio_repo",
	remote = "https://github.com/boostorg/ratio",
	commit = "da935d6c5f963dcfa2389d20a2d79e57d231d40c",
	build_file = "external_builds/boost/ratio.BUILD",
)

bind(
    name = "boost_ratio",
    actual = "@ratio_repo//:ratio",
)

new_git_repository(
	name = "regex_repo",
	remote = "https://github.com/boostorg/regex",
	commit = "a824b7d236e1084e06a3835d02cacc35772462d1",
	build_file = "external_builds/boost/regex.BUILD",
)

bind(
    name = "boost_regex",
    actual = "@regex_repo//:regex",
)

new_git_repository(
	name = "serialization_repo",
	remote = "https://github.com/boostorg/serialization",
	commit = "df38b48016fa0d27b8e400c8051976f35021e8a5",
	build_file = "external_builds/boost/serialization.BUILD",
)

bind(
    name = "boost_serialization",
    actual = "@serialization_repo//:serialization",
)

new_git_repository(
	name = "smart_ptr_repo",
	remote = "https://github.com/boostorg/smart_ptr",
	commit = "c87b6e8af8f30130c708cba7ba393c542c489aad",
	build_file = "external_builds/boost/smart_ptr.BUILD",
)

bind(
    name = "boost_smart_ptr",
    actual = "@smart_ptr_repo//:smart_ptr",
)

new_git_repository(
	name = "static_assert_repo",
	remote = "https://github.com/boostorg/static_assert",
	commit = "0d27f7bcf621a6fb9ba639e21fab6216442bee23",
	build_file = "external_builds/boost/static_assert.BUILD",
)

bind(
    name = "boost_static_assert",
    actual = "@static_assert_repo//:static_assert",
)

new_git_repository(
	name = "system_repo",
	remote = "https://github.com/boostorg/system",
	commit = "388b3497af4b205ff7e8c67ea306f57eea629ae3",
	build_file = "external_builds/boost/system.BUILD",
)

bind(
    name = "boost_system",
    actual = "@system_repo//:system",
)

new_git_repository(
	name = "thread_repo",
	remote = "https://github.com/boostorg/thread",
	commit = "6ec16408fc8d051109d5518786daf12ee6f7d63b",
	build_file = "external_builds/boost/thread.BUILD",
)

bind(
    name = "boost_thread",
    actual = "@thread_repo//:thread",
)

new_git_repository(
	name = "throw_exception_repo",
	remote = "https://github.com/boostorg/throw_exception",
	commit = "fa2195c268ab45ce1f1e9cdfc94a3ca7df80cfa9",
	build_file = "external_builds/boost/throw_exception.BUILD",
)

bind(
    name = "boost_throw_exception",
    actual = "@throw_exception_repo//:throw_exception",
)

new_git_repository(
	name = "tokenizer_repo",
	remote = "https://github.com/boostorg/tokenizer",
    commit= "6b83489ede7c2bf25073a05abb62655cd1235e26",
	build_file = "external_builds/boost/tokenizer.BUILD",
)

bind(
    name = "boost_tokenizer",
    actual = "@tokenizer_repo//:tokenizer",
)

new_git_repository(
	name = "type_index_repo",
	remote = "https://github.com/boostorg/type_index",
	commit = "31ec1d2524d7fa926c7384d38001b675ee2ad038",
	build_file = "external_builds/boost/type_index.BUILD",
)

bind(
    name = "boost_type_index",
    actual = "@type_index_repo//:type_index",
)

new_git_repository(
	name = "type_traits_repo",
	remote = "https://github.com/boostorg/type_traits",
	commit = "5f82b5ac5039031ad6bf6a2a592bd0c8caf18630",
	build_file = "external_builds/boost/type_traits.BUILD",
)

bind(
    name = "boost_type_traits",
    actual = "@type_traits_repo//:type_traits",
)

new_git_repository(
	name = "tuple_repo",
	remote = "https://github.com/boostorg/tuple",
	commit = "158c7ef640a0d147af11044d6c62723c07a10473",
	build_file = "external_builds/boost/tuple.BUILD",
)

bind(
    name = "boost_tuple",
    actual = "@tuple_repo//:tuple",
)

new_git_repository(
	name = "tr1_repo",
	remote = "https://github.com/boostorg/tr1",
	commit = "9f28b876b5750651a78acc802eed0d9ec6727438",
	build_file = "external_builds/boost/tr1.BUILD",
)

bind(
    name = "boost_tr1",
    actual = "@tr1_repo//:tr1",
)

new_git_repository(
	name = "utility_repo",
	remote = "https://github.com/boostorg/utility",
	commit = "181f302ee4c8153aa2ad91bfbc123294a34e05cb",
	build_file = "external_builds/boost/utility.BUILD",
)

bind(
    name = "boost_utility",
    actual = "@utility_repo//:utility",
)

new_git_repository(
	name = "variant_repo",
	remote = "https://github.com/boostorg/variant",
	commit = "dbb832c81e153ae6abd3c6245064e4c3774c2c93",
	build_file = "external_builds/boost/variant.BUILD",
)

bind(
    name = "boost_variant",
    actual = "@variant_repo//:variant",
)


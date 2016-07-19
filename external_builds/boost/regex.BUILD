licenses(["notice"])

load("/tools/build_rules/boost", "boost_library")

boost_library(
    name = "regex",
    defines = [
        "BOOST_FALLTHROUGH",
    ],
    srcs = glob([
        "regex/src/*.cpp",
        "regex/src/*.hpp",
    ]),
    deps = [
        "//external:boost_assert",
        "//external:boost_config",
        "//external:boost_functional",
        "//external:boost_integer",
        "//external:boost_mpl",
        "//external:boost_smart_ptr",
        "//external:boost_throw_exception",
        "//external:boost_type_traits",
    ],
)

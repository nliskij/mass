licenses(["notice"])

load("/tools/build_rules/boost", "boost_library")

boost_library(
    name = "filesystem",
    srcs = glob([
        "filesystem/src/*.cpp",
    ]),
    deps = [
        "//external:boost_config",
        "//external:boost_functional",
        "//external:boost_io",
        "//external:boost_iterator",
        "//external:boost_range",
        "//external:boost_smart_ptr",
        "//external:boost_system",
        "//external:boost_type_traits",
    ],
)

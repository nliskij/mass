licenses(["notice"])

load("/tools/build_rules/boost", "boost_library")

boost_library(
    name = "system",
    srcs = glob([
        "system/src/*.cpp",
    ]),
    deps = [
        "//external:boost_assert",
        "//external:boost_config",
        "//external:boost_core",
        "//external:boost_predef",
    ],
    defines = [
      "BOOST_ERROR_CODE_HEADER_ONLY",
    ],
)

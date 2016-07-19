licenses(["notice"])

load("/tools/build_rules/boost", "boost_library")

boost_library(
    name = "tr1",
    defines = [
        "BOOST_FALLTHROUGH",
    ],
    deps = [
        "//external:boost_config",
    ],
)

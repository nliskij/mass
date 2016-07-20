licenses(['notice'])

cc_library(
    name = "opencv",
    includes = ["include"],
    hdrs = glob([
        "include/**/*.hpp",
        "include/**/*.h",
    ]),
    srcs = glob(["lib/*.so*"]),
    visibility = ["//visibility:public"],
    linkstatic=1,
)

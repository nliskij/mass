def empty_main_if_asan(srcs):
    return select({
        '@//tools:has_asan': ['@//tools/cpp:empty_main'],
        '//conditions:default': srcs,
    })

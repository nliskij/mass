load('/tools/build_rules/protobuf', 'proto_cc_library')

cc_binary(
    name = 'test_tcmalloc_binary',
    srcs = [
        'test_tcmalloc.cc',
    ],
)

sh_test(
    name = 'test_tcmalloc',
    srcs = [
        'test_tcmalloc.sh',
    ],
    data = [
        ':test_tcmalloc_binary',
    ],
    size = 'small',
)

proto_cc_library(
    name = 'test_proto_library',
    src = 'proto.proto',
)

cc_test(
    name = 'proto_build_test',
    srcs = [
        'proto.cpp',
    ],
    deps = [
        ':test_proto_library',
        '//controve/tests:googletest',
    ],
    size = 'small',
)

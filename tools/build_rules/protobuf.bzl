def _proto_cc_library_impl(ctx):
    message = 'Building %s and %s from %s' % (ctx.outputs.pb_h.short_path,
                                              ctx.outputs.pb_cc.short_path,
                                              ctx.file.src.short_path)

    ctx.action(
        inputs = ctx.files.src + ctx.files._google_include_protos,
        executable = ctx.executable._protoc,
        arguments = [
            '--cpp_out=%s' % ctx.configuration.genfiles_dir.path,
            '-I.',
            '-Ithird_party/protobuf/src',
            ctx.file.src.path,
        ],
        mnemonic = 'ProtocCc',
        progress_message = message,
        outputs = [
            ctx.outputs.pb_h,
            ctx.outputs.pb_cc,
        ],
    )

def _proto_cc_library_outputs(attr):
    rootname = attr.src.name[:-len('.proto')]
    print("%s" % attr.src.name)
    return {
        'pb_h': '%s.pb.h' % rootname,
        'pb_cc': '%s.pb.cc' % rootname,
    }

_proto_cc_library = rule(
    implementation = _proto_cc_library_impl,
    attrs = {
        'src': attr.label(
            allow_files = ['.proto'],
            mandatory = True,
            single_file = True,
        ),
        '_protoc': attr.label(
            default = Label('//third_party/protobuf:protoc'),
            executable = True,
            cfg = HOST_CFG,
        ),
        '_google_include_protos': attr.label(
            default = Label('//third_party/protobuf:well_known_protos'),
        ),
    },
    outputs = _proto_cc_library_outputs,
    output_to_genfiles = True,
)

def proto_cc_library(name, src, visibility = None):
    _proto_cc_library(
        name = '%s__proto_srcs' % name,
        src = src,
        visibility = ['//visibility:private'],
    )
    rootname = src[:-len('.proto')]
    native.cc_library(
        name = name,
        copts = [ '-Wno-unused-parameter' ],
        srcs = [ '%s.pb.cc' % rootname ],
        hdrs = [ '%s.pb.h' % rootname ],
        deps = [ '//third_party/protobuf' ],
        visibility = visibility,
    )

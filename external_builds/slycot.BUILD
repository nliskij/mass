licenses(['restricted'])

load('/tools/build_rules/fortran', 'fortran_library')

# We need to modify _wrapper.pyf so that it will generate a library file
# in a completely different location. Usually, the .so file is placed in
# the slycot directory and we can't have that so we create a custom
# wrapper to load it from the bazel-build path.
genrule(
    name = '_fortranwrapper_pyf',
    srcs = ['slycot/src/_wrapper.pyf'],
    outs = ['slycot/src/_fortranwrapper.pyf'],
    cmd = 'cat $(SRCS) | sed \'s/_wrapper/_fortranwrapper/\' > $(OUTS)',
)

genrule(
    name = '_fortranwrappermodule',
    srcs = [
        'slycot/src/analysis.pyf',
        'slycot/src/synthesis.pyf',
        'slycot/src/_fortranwrapper.pyf',
        'slycot/src/math.pyf',
        'slycot/src/transform.pyf',
    ],
    outs = ['_fortranwrappermodule.c'],
    cmd = '/usr/bin/python /usr/bin/f2py $(location :slycot/src/_fortranwrapper.pyf) --include-paths external/slycot_repo/slycot/src/ --coutput $(OUTS)',
)

cc_library(
    name = 'slycot_c',
    srcs = [
        ':_fortranwrappermodule',
    ],
    deps = [
        ':fortran_files',
        '@usr_repo//:python2.7_lib',
        '@usr_repo//:python2.7_f2py',
    ],
    copts = [
        '-Wno-error',
        '-Wno-incompatible-pointer-types-discards-qualifiers',
        '-Wno-cast-align',
        '-Wno-unused-parameter',
        '-Wno-missing-field-initializers',
        '-Wno-unused-function',
    ],
)

fortran_library(
    name = 'fortran_files',
    srcs = glob(['slycot/src/*.f']),
)

cc_binary(
    name = '_fortranwrapper.so',
    deps = [
        ':fortran_files',
        ':slycot_c',
    ],
    linkopts = ['-shared', '-lblas', '-llapack'],
    linkstatic=0,
)

genrule(
    name = '_wrapper',
    outs = ['slycot/_wrapper.py'],
    cmd = 'echo "from _fortranwrapper import *" > $(OUTS)',
    output_to_bindir=1,
)

py_library(
    name = 'slycot',
    srcs = [
        'slycot/analysis.py',
        'slycot/examples.py',
        'slycot/__init__.py',
        'slycot/math.py',
        'slycot/synthesis.py',
        'slycot/transform.py',
        ':_wrapper',
    ],
    data = [
        ':_fortranwrapper.so',
    ],
    visibility = ['//visibility:public'],
)

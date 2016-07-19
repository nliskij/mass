includes_pattern_base = "include"
include_pattern_h = includes_pattern_base + "/boost/**/*.h"
include_pattern_pp = includes_pattern_base + "/boost/**/*pp"

def includes_list(library_name):
  return [ includes_pattern_base ]

def hdr_list(library_name):
  return native.glob([
    include_pattern_h,
    include_pattern_pp,
  ])

def boost_library(name, defines=None, includes=None, hdrs=None, srcs=None, deps=None, copts=None, linkopts=None):

    if defines == None:
        defines = []

    if includes == None:
        includes = []

    if hdrs == None:
        hdrs = []

    if srcs == None:
        srcs = []

    if deps == None:
        deps = []

    if copts == None:
        copts = []

    if linkopts == None:
        linkopts = []

    return native.cc_library(
        name = name,
        visibility = ["//visibility:public"],
        defines = defines,
        includes = includes_list(name) + includes,
        hdrs = hdr_list(name) + hdrs,
        srcs = [] + srcs,
        deps = deps,
        copts = copts,
        linkopts = linkopts,
    )


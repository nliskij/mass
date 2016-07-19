licenses(['notice'])

load("/tools/build_rules/boost", "boost_library")

boost_library(
  name = "lexical_cast",
  deps = [
    "//external:boost_numeric_conversion",
    "//external:boost_array",
    "//external:boost_container",
    "//external:boost_math",
    "//external:boost_range",
    "//external:boost_static_assert",
    "//external:boost_mpl",
    "//external:boost_throw_exception",
    "//external:boost_type_traits",
    "//external:boost_utility",
  ],
)

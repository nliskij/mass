licenses(['notice'])

load("/tools/build_rules/boost", "boost_library")

boost_library(
  name = "asio",
  deps = [
    "//external:boost_thread",
    "//external:boost_serialization",
    "//external:boost_date_time",
    "//external:boost_regex",
    "//external:boost_system",
  ],
)

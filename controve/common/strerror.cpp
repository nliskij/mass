#include "controve/common/strerror.hpp"

#include <sys/types.h>
#include <cstdio>
#include <cassert>
#include <cstring>

namespace controve {
namespace {

const size_t buffer_size = 128;

__attribute__((unused))
char *controve_strerror_handle(__attribute__((unused)) int error, char *ret,
    __attribute__((unused)) char *buffer) {
  return ret;
}

__attribute__((unused))
char* controve_strerror_handle(int error, int ret, char* buffer) {
  if (ret != 0) {
#ifndef NDEBUG
    const int r =
#endif
      snprintf(buffer, buffer_size, "Unknown error %d", error);
    assert (r > 0);
  }
  return buffer;
}

}  // namespace

const char *controve_strerror(int error) {
  static thread_local char buffer[buffer_size];

  return controve_strerror_handle(
      error, strerror_r(error, buffer, sizeof(buffer)), buffer);
}
}  // namespace controve

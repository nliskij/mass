#ifndef CONTROVE_COMMON_DIE_HPP
#define CONTROVE_COMMON_DIE_HPP

#include <cstdarg>
#include "controve/common/config.hpp"

namespace controve {

void die(const char *format, ...)
    __attribute__((noreturn))
    __attribute__((format(COMPILER_PRINTF_FORMAT, 1, 2)));
void vdie(const char *format, va_list args)
    __attribute__((noreturn))
    __attribute__((format(COMPILER_PRINTF_FORMAT, 1, 0)));

#define pdie(format, args...)                             \
  do {                                                    \
    const int err = errno;                                \
    ::controve::die(format " because of %d (%s)", ##args, \
        err, controve_strerror(err));                     \
  } while (false)

#define prdie(error, format, args...)                       \
  do {                                                      \
    ::controve::die(format " because of %d (%s)", ##args,   \
        error, controve_strerror(error))                    \
  } while (false)

}  // namespace controve

#endif  // CONTROVE_COMMON_DIE_HPP

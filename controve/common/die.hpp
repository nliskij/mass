#ifndef CONTROVE_COMMON_DIE_HPP
#define CONTROVE_COMMON_DIE_HPP

#include <cstdarg>
#include "controve/common/config.hpp"

/// @file die.hpp
/// @author Lee Mracek
/// @brief Utility to log a message and then die
/// @bugs No known bugs

namespace controve {

/// print formatted message and then abort with SIGABRT
/// @param format the format-string to log
/// @param ... the formatted variables
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

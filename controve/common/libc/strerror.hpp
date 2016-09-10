#ifndef CONTROVE_COMMON_LIBC_STRERROR_HPP_
#define CONTROVE_COMMON_LIBC_STRERROR_HPP_

/// @file strerror.hpp
/// @brief Thread-safe implemenation of the POSIX function strerror(3)
/// @author Lee Mracek
/// @bug No known bugs
///
/// A short list of POSIX functions are not required to be thread-
/// safe. Unfortunately, we need them to be thread-safe, so the ones that we
/// use need to be rewritten. A full list can be found at
/// http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_09_01

/// @brief Custom implemenation of strerror(3) to be thread-safe
/// Essentially this acts as a safe wrapper for strerror(3).
///
/// @param error the ERRNO reported from the command/OS
/// @return A char* array containing the user-friendly form of the error 
const char *controve_strerror(int error);

#endif  // CONTROVE_COMMON_LIBC_STRERROR_HPP_

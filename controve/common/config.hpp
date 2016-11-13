#ifndef CONTROVE_COMMON_CONFIG_HPP
#define CONTROVE_COMMON_CONFIG_HPP

#ifdef __clang__
#define COMPILER_PRINTF_FORMAT __printf__
#else
#define COMPILER_PRINTF_FORMAT gnu_printf
#endif

// LOGGING

static const int LOG_MESSAGE_LEN = 400;
static const int LOG_MESSAGE_NAME_LEN = 100;

#endif  // CONTROVE_COMMON_CONFIG_HPP

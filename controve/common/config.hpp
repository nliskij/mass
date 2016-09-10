#ifndef CONTROVE_COMMON_CONFIG_HPP
#define CONTROVE_COMMON_CONFIG_HPP

#ifdef __clang__
#define COMPILER_PRINTF_FORMAT __printf__
#else
#define COMPILER_PRINTF_FORMAT gnu_printf
#endif

#endif  // CONTROVE_COMMON_CONFIG_HPP

#ifndef CONTROVE_COMMON_LOGGING_LOGGING_HPP
#define CONTROVE_COMMON_LOGGING_LOGGING_HPP

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cerrno>

#include "controve/common/config.hpp"
#include "controve/common/libc/strerror.hpp"

using log_level = uint8_t;

static const log_level DEBUG = 0;
static const log_level INFO = 1;
static const log_level WARNING = 2;
static const log_level ERROR = 3;
static const log_level FATAL = 4;
static const log_level LOG_UNKNOWN = 5;

void doLog(log_level level, const char *format, ...)
  __attribute__((format(COMPILER_PRINTF_FORMAT, 2, 3)));

#define STRINGIFY(x) TO_STRING(x)
#define TO_STRING(x) #x

#define LOG_CURRENT_FUNCTION __PRETTY_FUNCTION__

#define LOG_SOURCENAME __FILE__

#define LOG(level, format, args...)                                         \
  do {                                                                      \
    doLog(level, LOG_SOURCENAME ": " STRINGIFY(__LINE__) ": %s: " format,   \
          LOG_CURRENT_FUNCTION, ##args);                                    \
    if (level == FATAL) {                                                   \
      fprintf(stderr, "doLog(FATAL) fell through!\n");                      \
      printf("see stderr\n");                                               \
      abort();                                                              \
    }                                                                       \
  } while(0)

#define PLOG(level, format, args...) PELOG(level, errno, format, ##args)

#define PELOG(level, errorarg, format, args...)                             \
  do {                                                                      \
    const int error = errorarg;                                             \
    LOG(level, format " due to %d (%s)\n", ##args, error,                   \
        controve_strerror(error));                                          \
  } while(0)

#define LOG_DYNAMIC(level, format, args...)                             \
  do {                                                                  \
    static char log_buf[LOG_MESSAGE_LEN];                               \
    int ret = snprintf(log_buf, sizeof(log_buf), format, ##args);       \
    if (ret < 0 || (uintmax_t)ret >= LOG_MESSAGE_LEN) {                 \
      LOG(ERROR, "next message was too long so not subbing in args\n"); \
      LOG(level, "%s", format);                                         \
    } else {                                                            \
      LOG(level, "%s", log_buf);                                        \
    }                                                                   \
  } while (0)

namespace controve {

#define CHECK(condition)                            \
  if (__builtin_expect(!(condition), 0)) {          \
      LOG(FATAL, "CHECK(%s) failed\n", #condition); \
  }                                                 \

#define DEFINE_CHECK_OP_IMPL(name, op)                                      \
  template <typename T1, typename T2>                                       \
  inline void LogImpl##name(const T1 &v1, const T2 &v2,                     \
                            const char *text) {                             \
    if(!__builtin_expect(v1 op v2, 1)) {                                    \
      doLog(FATAL,                                                          \
            LOG_SOURCENAME ": " STRINGIFY(__LINE__) ": CHECK(%s) failed\n", \
            text);                                                          \
      fprintf(stderr, "doLog(FATAL) fell through!\n");                      \
      printf("see stderr\n");                                               \
      abort();                                                              \
    }                                                                       \
  }                                                                         \
  inline void LogImpl##name(int v1, int v2, const char *text) {             \
    ::controve::LogImpl##name<int, int>(v1, v2, text);                      \
  }

DEFINE_CHECK_OP_IMPL(Check_EQ, ==)
DEFINE_CHECK_OP_IMPL(Check_NE, !=)
DEFINE_CHECK_OP_IMPL(Check_LE, <=)
DEFINE_CHECK_OP_IMPL(Check_LT, < )
DEFINE_CHECK_OP_IMPL(Check_GE, >=)
DEFINE_CHECK_OP_IMPL(Check_GT, > )

#define CHECK_OP(name, op, val1, val2)       \
  ::controve::LogImplCheck##name(val1, val2, \
                                 STRINGIFY(val1) STRINGIFY(op) STRINGIFY(val2))

#define CHECK_EQ(val1, val2) CHECK_OP(_EQ, ==, val1, val2)
#define CHECK_NE(val1, val2) CHECK_OP(_NE, !=, val1, val2)
#define CHECK_LE(val1, val2) CHECK_OP(_LE, <=, val1, val2)
#define CHECK_LT(val1, val2) CHECK_OP(_LT, < , val1, val2)
#define CHECK_GE(val1, val2) CHECK_OP(_GE, >=, val1, val2)
#define CHECK_GT(val1, val2) CHECK_OP(_GT, > , val1, val2)

template <typename T>
inline T* CheckNotNull(const char *value_name, T *t) {
  if (t == NULL) {
      LOG(FATAL, "'%s' must not be NULL\n", value_name);
  }
  return t;
}

#define CHECK_NOTNULL(val) ::controve::CheckNotNull(STRINGIFY(val), val)

inline int CheckSyscall(const char *syscall_string, int value) {
  if (__builtin_expect(value == -1, false)) {
      PLOG(FATAL, "%s failed", syscall_string);
  }
  return value;
}

inline void CheckSyscallReturn(const char *syscall_string, int value) {
    if(__builtin_expect(value != 0, false)) {
      PELOG(FATAL, value, "%s failed", syscall_string);
    }
}

#define PCHECK(syscall) ::controve::CheckSyscall(STRINGIFY(syscall), syscall)

#define PRCHECK(syscall) ::controve::CheckSyscallReturn(STRINGIFY(syscall), syscall)

}  // namespace controve

#endif

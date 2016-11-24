#ifndef CONTROVE_COMMON_LOGGING_LOGGING_HPP
#define CONTROVE_COMMON_LOGGING_LOGGING_HPP

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cerrno>
#include <functional>
#include <cstdarg>

#include "controve/common/config.hpp"
#include "controve/common/libc/strerror.hpp"

using log_level = uint8_t;

#define DECLARE_LEVELS \
DECLARE_LEVEL(DEBUG,       0); \
DECLARE_LEVEL(INFO,        1); \
DECLARE_LEVEL(WARNING,     2); \
DECLARE_LEVEL(ERROR,       3); \
DECLARE_LEVEL(FATAL,       4); \
DECLARE_LEVEL(LOG_UNKNOWN, 5); 

#define DECLARE_LEVEL(name, value) \
  static const log_level name = value;
  DECLARE_LEVELS;
#undef DECLARE_LEVEL

void logDo(log_level level, const char *format, ...)
  __attribute__((format(COMPILER_PRINTF_FORMAT, 2, 3)));

#define STRINGIFY(x) TO_STRING(x)
#define TO_STRING(x) #x

#define LOG_CURRENT_FUNCTION __func__ // __PRETTY_FUNCTION__

#define LOG_SOURCENAME __FILE__

#define LOG(level, format, args...)                                         \
  do {                                                                      \
    logDo(level, LOG_SOURCENAME ": " STRINGIFY(__LINE__) ": %s: " format,   \
          LOG_CURRENT_FUNCTION, ##args);                                    \
    if (level == FATAL) {                                                   \
      fprintf(stderr, "logDo(FATAL) fell through!\n");                      \
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
      logDo(FATAL,                                                          \
            LOG_SOURCENAME ": " STRINGIFY(__LINE__) ": CHECK(%s) failed\n", \
            text);                                                          \
      fprintf(stderr, "logDo(FATAL) fell through!\n");                      \
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

// non-api code

namespace logging {

struct MessageType;

void VaLog(log_level level, const char *format, va_list ap)
  __attribute((format(COMPILER_PRINTF_FORMAT, 2, 0)));

class Handler {
  public:
    Handler() : nextptr(nullptr) {}

    Handler *next() { return nextptr; }

    virtual void setNext(Handler *next) { nextptr = next; }

  protected:
    __attribute__((format(COMPILER_PRINTF_FORMAT, 3, 0)))
    virtual void doLog(log_level level, const char *format, va_list ap) = 0;

    __attribute__((format(COMPILER_PRINTF_FORMAT, 3, 4)))
    virtual void doLogVa(log_level level, const char* format, ...) {
      va_list ap;
      va_start(ap, format);
      doLog(level, format, ap);
      va_end(ap);
    }

  private:
    __attribute__((format(COMPILER_PRINTF_FORMAT, 2, 0)))
    static void doVaLog(log_level, const char *format, va_list ap, int levels);

    __attribute__((format(COMPILER_PRINTF_FORMAT, 2, 0)))
    friend void vaLog(log_level, const char*, va_list);

    Handler *nextptr;
};

namespace internal {

size_t executeFormat(char *output, size_t output_size, const char *format,
                     va_list ap)
  __attribute__((format(COMPILER_PRINTF_FORMAT, 3, 0)));

void runWithCurrentHandler(int levels, ::std::function<void(Handler *)> function);

}  // namespace internal
}  // namespace logging
}  // namespace controve

#endif

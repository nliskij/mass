#ifndef CONTROVE_COMMON_HANDLERS_H
#define CONTROVE_COMMON_HANDLERS_H

#include <chrono>
#include <cstdint>
#include <cinttypes>
#include <cstring>
#include <cstdarg>

#include "controve/common/logging/frame.hpp"
#include "controve/common/config.hpp"
#include "controve/common/logging/logging.hpp"

namespace controve {
struct MessageType;

namespace logging {

struct LogMessage {
  enum class Type : uint8_t {
    STRING, STRUCT, MATRIX
  };

  ::std::chrono::time_point<::std::chrono::system_clock,
                            ::std::chrono::nanoseconds> time;
  size_t messageLength, nameLength;
  uint16_t sequence;
  pid_t source;
  static_assert(sizeof(source) == 4, "source wrong size");
  Type type;
  log_level level;
  char name[LOG_MESSAGE_NAME_LEN];

  union {
    char message[LOG_MESSAGE_LEN];
    struct {
      uint32_t type_id;
      size_t stringLength;
      char serialized[LOG_MESSAGE_LEN - sizeof(type) - sizeof(stringLength)];
    } structure;
    struct {
      uint32_t type;
      int rows, cols;
      size_t stringLength;
      char data[LOG_MESSAGE_LEN - sizeof(type) - sizeof(rows) - sizeof(cols)];
    } matrix;
  };
};

static inline const char *logStr(log_level level) {
#define DECLARE_LEVEL(name, value) if (level == name) return #name;
  DECLARE_LEVELS;
#undef DECLARE_LEVEL
  return "unknown";
}

static inline log_level strLog(const char *str) {
#define DECLARE_LEVEL(name, value) if (!::std::strcmp(str, #name)) return name;
  DECLARE_LEVELS;
#undef DECLARE_LEVEL
  return LOG_UNKNOWN;
}

class AbstractHandler : public Handler {
  private:
    __attribute__((format(COMPILER_PRINTF_FORMAT, 3, 0)))
    void doLog(log_level level, const char *format, va_list ap) override;
    virtual void handleMessage(const LogMessage &message) = 0;
};

/// Attach a handler to the current thread
void addHandler(Handler *handler);

void init();

void load();

void cleanup();

namespace internal {
__attribute__((format(COMPILER_PRINTF_FORMAT, 2, 0)))
void fillInMessage(log_level level, const char *format, va_list ap,
                    LogMessage *message);

__attribute__((format(COMPILER_PRINTF_FORMAT, 3, 4)))
static inline void fillInMessageVariadic(log_level level, LogMessage *message,
                                          const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  fillInMessage(level, format, ap, message);
  va_end(ap);
}

#define LOGGING_BASE_FORMAT "%.*s(%" PRId32 ")(%05" PRIu16 "): %-7s at %s"

void printMessage(FILE *output, const LogMessage &message);

void timestmp(char*,
              size_t,
              const ::std::chrono::time_point<::std::chrono::system_clock>&);

}  // namespace internal
}  // namespace logging
}  // namespace controve

#endif

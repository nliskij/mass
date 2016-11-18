#include "controve/common/logging/logging.hpp"

#include <cstring>
#include <algorithm>
#include <cstdarg>
#include <type_traits>

#include "controve/common/die.hpp"
#include "controve/common/logging/frame.hpp"

/// Implementation of non-api code in logging.hpp

namespace controve {
namespace logging {
namespace internal {

__attribute__((format(COMPILER_PRINTF_FORMAT, 3, 0)))
size_t executeFormat(char *output, size_t outputSize, const char *format,
                     va_list ap) {
  static const char *const continued = "...\n";
  const size_t size = outputSize - strlen(continued);
  const int ret = vsnprintf(output, size, format, ap);
  using retType = ::std::common_type<typeof(ret), typeof(size)>::type; 
  if (ret < 0) {
    PLOG(FATAL, "vnsprintf(%p, %zd, %s, args) failed",
         output, size, format);
  } else if (static_cast<retType>(ret) >= static_cast<retType>(size)) {
    std::memcpy(&output[size - 1], continued, strlen(continued) + 1);
  }
  return ::std::min<retType>(ret, size);
}

void runWithCurrentHandler(int levels,
                           ::std::function<void(Handler *)> function) {
  Frame *frame = Frame::get();

  Handler *const topHandler = frame->handler;
  Handler *newHandler = topHandler;
  Handler *handler = nullptr;

  for (int i = 0; i < levels; ++i) {
      handler = newHandler;
      if (newHandler == nullptr) {
          die("no logging implementation to use\n");
      }
      newHandler = handler->next();
  }
  frame->handler = newHandler;
  function(handler);
  frame->handler = topHandler;
}

}  // namespace internal

using internal::Frame;

void Handler::doVaLog(log_level level, const char *format, va_list ap,
                      int levels) {
  internal::runWithCurrentHandler(levels, [&](Handler *handler) {
    va_list ap1;
    va_copy(ap1, ap);
    handler->doLog(level, format, ap1);
    va_end(ap1);

    if (level == FATAL) {
      vdie(format, ap);
    }
  });
}

void vaLog(log_level level, const char* format, va_list ap) {
  Handler::doVaLog(level, format, ap, 1);
}

}  // namespace logging
}  // namespace controve

void logDo(log_level level, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  controve::logging::vaLog(level, format, ap);
  va_end(ap);
}

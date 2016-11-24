#ifndef CONTROVE_COMMON_LOGGING_FRAME_HPP_
#define CONTROVE_COMMON_LOGGING_FRAME_HPP_

#include <cinttypes>
#include <cstddef>
#include <sys/types.h>
#include <climits>

#include <atomic>

#include "controve/common/config.hpp"

namespace controve {
namespace logging {

class Handler;

namespace internal {

extern ::std::atomic<Handler *> globalTopHandler;

struct Frame {
  Frame();

  static Frame *get();

  static void deleteFrame();

  Handler *handler;

  char name[LOG_MESSAGE_NAME_LEN];
  size_t name_size;

  pid_t source;

  uint16_t sequence;
};

}  // namespace internal
}  // namespace logging
}  // namespace controve

#endif

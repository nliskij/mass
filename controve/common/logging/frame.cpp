#include "controve/common/logging/frame.hpp"

#include <string>
#include <cstring>
#include <memory>

#include <sys/types.h>
#include <sys/prctl.h>
#include <unistd.h>

#include "controve/common/die.hpp"

namespace controve {
namespace logging {
namespace internal {
namespace {

::std::string getLocalName() {
  static const size_t threadNameLength = 16;

  ::std::string processName(program_invocation_short_name);

  char threadNameArr[threadNameLength + 1];
  if (prctl(PR_GET_NAME, threadNameArr) != 0) {
    pdie("prctl(PR_GET_NAME, %p) failed", threadNameArr);
  }

  threadNameArr[sizeof(threadNameArr) - 1] = '\0';
  ::std::string threadName(threadNameArr);

  if (::std::strncmp(threadName.c_str(), processName.c_str(), 
              ::std::min(threadName.length(), processName.length())) == 0) {
    return processName;
  }

  return processName + '.' + threadName;
}

thread_local ::std::unique_ptr<Frame> myFrame = nullptr;

thread_local bool deleteCurrentFrame(false);

}  // namespace

::std::atomic<Handler *> globalTopHandler(nullptr);

Frame::Frame()
    : handler(globalTopHandler.load()),
      sequence(0) {
}

void reloadThreadName() {
  if (myFrame != nullptr) {
    ::std::string name = getLocalName();
    if (name.size() + 1 > sizeof(Frame::name)) {
      die("thread name '%s' is too long to log\n",
          name.c_str());
    }
    strcpy(myFrame->name, name.c_str());
    myFrame->name_size = name.size();
  }
}

Frame *Frame::get() {
  if (__builtin_expect(deleteCurrentFrame, false)) {
    myFrame.release();
    deleteCurrentFrame = false;
  }
  if (__builtin_expect(myFrame == nullptr, false)) {
    myFrame = ::std::unique_ptr<Frame>(new Frame);
    reloadThreadName();
    myFrame->source = getpid();
  }

  return myFrame.get();
}

void Frame::deleteFrame() {
  deleteCurrentFrame = true;
}

}  // namespace internal
}  // namespace logging
}  // namespace controve

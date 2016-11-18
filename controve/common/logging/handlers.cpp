#include "controve/common/logging/handlers.hpp"

#include <algorithm>
#include <cstdarg>
#include <cinttypes>
#include <cstdio>

#include <pthread.h>

#include "controve/common/die.hpp"
#include "controve/common/logging/frame.hpp"

namespace controve {
namespace logging {
namespace {

class RootHandler : public AbstractHandler {
  public:
    void haveOtherHandler() {
      onlyHandler = false;
    }

  private:
    void setNext(Handler *) override {
      LOG(FATAL, "Cannot add handler to root handler!\n");
    }

    void handleMessage(const LogMessage &message) override {
      internal::printMessage(stderr, message);
      if (!onlyHandler) {
        ::std::fputs("root logger used, see stderr\n", stdout);
      }
    }

    bool onlyHandler = false;
};

RootHandler *rootHandler = nullptr;

void setGlobalHandler(Handler *handler) {
  if (rootHandler == nullptr) {
    ::controve::die("Be sure to call logging::init()\n");
  }

  internal::Frame *frame = internal::Frame::get();
  frame->handler = handler;
  internal::globalTopHandler.store(handler);
}

void newFrame() {
  internal::Frame::deleteFrame();
}

void performInit() {
  newFrame();
  setGlobalHandler(rootHandler = new RootHandler());
}

}  // namespace

namespace internal {
namespace {

void fillInMessageRoot(log_level level, LogMessage *message) {
  Frame *frame = Frame::get();

  message->level = level;
  message->source = frame->source;
  ::std::memcpy(message->name, frame->name, frame->name_size);
  message->nameLength = frame->name_size;

  message->time =
    ::std::chrono::time_point_cast<::std::chrono::nanoseconds>(
        ::std::chrono::system_clock::now());

  message->sequence = frame->sequence++;
}

}  // namespace

void fillInMessage(log_level level, const char *format, va_list ap,
                   LogMessage *message) {
  fillInMessageRoot(level, message);

  message->messageLength = 
    executeFormat(message->message, sizeof(message->message), format, ap);
  message->type = LogMessage::Type::STRING;
}

void timestmp(char *output, size_t count,
              const ::std::chrono::time_point
              <::std::chrono::system_clock> &now) {
  ::std::chrono::microseconds usecs =
    ::std::chrono::duration_cast<::std::chrono::microseconds>(
        now.time_since_epoch());

  ::std::chrono::seconds secs =
    ::std::chrono::duration_cast<::std::chrono::seconds>(usecs);

  ::std::time_t t = secs.count();
  unsigned int fsecs = usecs.count() % 1000000;

  
  strftime(output, sizeof(output), "%D %Z-%H:%M:%S", localtime(&t));
  
  // non-literal

  char timestr[8];
  snprintf(timestr, count, ".%06u", fsecs);
  strcat(output, timestr);
}


void printMessage(FILE *output, const LogMessage &message) {
#define ARGS \
  static_cast<int>(message.nameLength), message.name, message.source, \
  message.sequence, logStr(message.level)
  switch(message.type) {
    case LogMessage::Type::STRING:
      char outstr[100];
      timestmp(outstr, sizeof(outstr), message.time);
      fprintf(output, LOGGING_BASE_FORMAT "%.*s", ARGS, outstr, 
          static_cast<int>(message.messageLength), message.message);
      break;
    case LogMessage::Type::STRUCT:
    case LogMessage::Type::MATRIX:
    default:
      const char enumStrings[3][7] = {{"STRING"}, {"STRUCT"}, {"MATRIX"}};
      die("%s not implemented yet\n",
          enumStrings[static_cast<int>(message.type)]);
  }
#undef ARGS
}
}  // namespace internal

void AbstractHandler::doLog(log_level level, const char *format, va_list ap) {
  LogMessage message;
  internal::fillInMessage(level, format, ap, &message);
  handleMessage(message);
}

void addHandler(Handler *handler) {
  internal::Frame *frame = internal::Frame::get();

  if(handler->next() != NULL) {
    LOG(FATAL, "%p has a next handler, but not being used yet\n", handler);
  }

  Handler *old = frame->handler;
  if (old != NULL) {
    handler->setNext(old);
  }
  setGlobalHandler(handler);
  rootHandler->haveOtherHandler();
}

void init() {
  auto once_init = PTHREAD_ONCE_INIT;
  pthread_once(&once_init, &performInit);
}

void load() {
  internal::Frame::get();
}

void cleanup() {
  internal::Frame::deleteFrame();
}

}  // namespace logging
}  // namespace controve

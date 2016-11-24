#include <string>

#include <cinttypes>

#include "gtest/gtest.h"

#include "controve/common/logging/handlers.hpp"

using ::testing::AssertionResult;
using ::testing::AssertionSuccess;
using ::testing::AssertionFailure;

namespace controve {
namespace logging {
namespace testing {

class TestLogHandler : public AbstractHandler {
  virtual void handleMessage(const LogMessage &message) override {
    message_ = message;

    if (message.level == FATAL) {
      internal::printMessage(stderr, message_);
      abort();
    }

    used_ = true;
  }

  LogMessage message_;

  public:
    const LogMessage &message() { return message_; }
    bool used() { return used_; }
    void reset_used() { used_ = false; }

    TestLogHandler() : used_(false) {}

    bool used_;
};

class LoggingTest : public ::testing::Test {
  protected:
    AssertionResult wasAnythingLogged() {
      if (logHandler->used()) {
        return AssertionSuccess() << "read message '" <<
          logHandler->message().message << "'";
      }
      return AssertionFailure();
    }

    AssertionResult wasLogged(log_level level, const ::std::string message) {
      if (!logHandler->used()) {
        return AssertionFailure() << "nothing was logged";
      }
      if (logHandler->message().level != level) {
        return AssertionFailure() << "a message with level " <<
          logStr(logHandler->message().level) <<
          " was logged instead of " << logStr(level);
      }
      internal::Frame *frame = internal::Frame::get();
      if (logHandler->message().source != frame->source) {
        LOG(FATAL, "got a message from %" PRIu32 ", but we're %" PRIu32 "\n",
            static_cast<uint32_t>(logHandler->message().source),
            static_cast<uint32_t>(frame->source));
      }
      if (logHandler->message().nameLength != frame->name_size ||
          memcmp(logHandler->message().name, frame->name,
          frame->name_size) != 0) {
        LOG(FATAL, "got a message from %.*s, but we're %s\n",
            static_cast<int>(logHandler->message().nameLength),
            logHandler->message().name, frame->name);
      }
      if (strstr(logHandler->message().message, message.c_str())
          == NULL) {
        return AssertionFailure() << "got a message of '" <<
          logHandler->message().message <<
          "' but expected it to contain '" << message << "'";
      }

      return AssertionSuccess() << logHandler->message().message;
    }
  private:
    void SetUp() override {
      static bool first = true;
      if (first) {
        first = false;

        init();
        addHandler(logHandler = new TestLogHandler());
      }
    }

    void TearDown() override {
      cleanup();
    }

    static TestLogHandler *logHandler;
};

TestLogHandler *LoggingTest::logHandler(NULL);

typedef LoggingTest LoggingDeathTest;

TEST_F(LoggingTest, Basic) {
  EXPECT_FALSE(wasAnythingLogged());
  LOG(INFO, "test log 1\n");
  EXPECT_TRUE(wasLogged(INFO, "test log 1\n"));
  LOG(INFO, "test log 2\n");
  EXPECT_FALSE(wasLogged(INFO, "test log 22\n"));
  LOG(ERROR, "test log 2=%d\n", 55);
  EXPECT_TRUE(wasLogged(ERROR, "test log 2=55\n"));
  LOG(ERROR, "test log 3\n");
  EXPECT_FALSE(wasLogged(WARNING, "test log 3\n"));
  LOG(WARNING, "test log 4\n");
  EXPECT_TRUE(wasAnythingLogged());
}

TEST_F(LoggingDeathTest, Fatal) {
  ASSERT_EXIT(LOG(FATAL, "this should crash it\n"),
              ::testing::KilledBySignal(SIGABRT),
              "this should crash it");
}

TEST_F(LoggingDeathTest, PCHECK) {
  EXPECT_DEATH(PCHECK(fprintf(stdin, "error(duh)")),
               ".*fprintf\\(stdin, \"error\\(duh\\)\"\\).*failed.*");
}

TEST_F(LoggingTest, PCHECK) {
  EXPECT_EQ(7, PCHECK(printf("abc123\n")));
}

TEST_F(LoggingTest, PrintfFormatting) {
  LOG(INFO, "test log %%1 %%d\n");
  EXPECT_TRUE(wasLogged(INFO, "test log %1 %d\n"));
  LOG_DYNAMIC(WARNING, "test log %%2 %%f\n");
  EXPECT_TRUE(wasLogged(WARNING, "test log %2 %f\n"));
}

}  // namespace testing
}  // namespace logging
}  // namespace controve

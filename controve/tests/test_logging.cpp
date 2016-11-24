#include "controve/tests/test_logging.hpp"

#include <cstdio>
#include <vector>
#include <pthread.h>
#include <cstring>
#include <mutex>

#include "gtest/gtest.h"

#include "controve/common/logging/handlers.hpp"

using ::controve::logging::LogMessage;

namespace controve {
namespace testing {
namespace {

class TestLogHandler : public logging::AbstractHandler {
  public:
    const ::std::vector<LogMessage> &messages() { return messages_; }

    static TestLogHandler *getInstance() {
      static TestLogHandler *instance = nullptr;
      if (instance == nullptr) {
        instance = new TestLogHandler();
      }

      return instance;
    }

    void clearMessages() {
      ::std::lock_guard<::std::mutex> guard(messages_mutex);
      messages_.clear();
    }

    void printAllMessages() {
      ::std::lock_guard<::std::mutex> guard(messages_mutex);
      for (auto &i : messages_) {
        logging::internal::printMessage(stdout, i);
      }
    }

    void setOutputFile(const char *filename) {
      if (::std::strcmp("-", filename) != 0) {
        FILE *newfile = ::std::fopen(filename, "w");
        if (newfile) {
          outputfile = newfile;
        }
      }
    }

    void printMessagesAsTheyCome() {printMessagesAsCome = true; }

  private:
    TestLogHandler() {}
    ~TestLogHandler() {
      if (outputfile != stdout) {
        ::std::fclose(outputfile);
      }
    }

    virtual void handleMessage(const LogMessage &message) override {
      ::std::lock_guard<::std::mutex> guard(messages_mutex);
      if (message.level == FATAL || printMessagesAsCome) {
        logging::internal::printMessage(outputfile, message);
      }

      messages_.push_back(message);
    }

    ::std::vector<LogMessage> messages_;
    bool printMessagesAsCome = false;
    FILE *outputfile = stdout;
    ::std::mutex messages_mutex;
};

class MyTestEventListener : public ::testing::EmptyTestEventListener {
  virtual void onTestStart(const ::testing::TestInfo &) {
    TestLogHandler::getInstance()->clearMessages();
  }

  virtual void OnTestEnd(const ::testing::TestInfo &testInfo) {
    if (testInfo.result()->Failed()) {
      ::std::printf("Test %s failed, Use '--print-logs' to see log messages\n",
          testInfo.name());
    }
  }

  virtual void OnTestPartResult(const ::testing::TestPartResult &result) {
    if (result.failed()) {
      const char *failure_type = "unknown";
      switch (result.type()) {
        case ::testing::TestPartResult::Type::kNonFatalFailure:
          failure_type = "EXPECT";
          break;
        case ::testing::TestPartResult::Type::kFatalFailure:
          failure_type = "ASSERT";
          break;
        case ::testing::TestPartResult::Type::kSuccess:
          break;
      }
      logDo(ERROR, "%s: %d: gtest %s failure\n%s\n",
          result.file_name(),
          result.line_number(),
          failure_type,
          result.message());
    }
  }
};

void doEnableTestLogging() {
  logging::init();
  logging::addHandler(TestLogHandler::getInstance());

  ::testing::UnitTest::GetInstance()->listeners().Append(
      new MyTestEventListener());
}

}  // namespace

auto pthreadwhatever = PTHREAD_ONCE_INIT;

void enableTestLogging() {
  pthread_once(&pthreadwhatever, doEnableTestLogging); 
}

void setLogFile(const char *filename) {
  TestLogHandler::getInstance()->setOutputFile(filename);
}

void forcePrintLogsDuringTests() {
  TestLogHandler::getInstance()->printMessagesAsTheyCome();
}

}  // namespace testing
}  // namespace controve

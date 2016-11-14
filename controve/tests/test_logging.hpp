#ifndef CONTROVE_TESTS_TEST_LOGGING_H
#define CONTROVE_TESTS_TEST_LOGGING_H

namespace controve {
namespace testing {

void enableTestLogging();

void setFileName(const char *filename);

void forcePrintsDuringTests();
}  // namespace testing
}  // namespace controve

#endif

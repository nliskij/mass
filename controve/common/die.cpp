#include "controve/common/die.hpp"

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <unistd.h>

namespace controve {
void die(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vdie(format, args);
}

namespace {

const std::string getFilename() {
  char *filename;
  if (asprintf(&filename, "/tmp/controve_fatal_error.%ju",
               static_cast<uintmax_t>(getpid())) > 0) {
    std::string ret(filename);
    free(filename);
    return ret;
  } else {
    ::std::fprintf(stderr, "fatal error: asprintf(%p, \"format-string\", %ju)"
        " failed with %d\n", &filename,
        static_cast<uintmax_t>(getpid()), errno);
    return std::string();
  }
}

}  // namespace

void vdie(const char *format, va_list args) {
  va_list args1, args2;

  ::std::fputs("controve FATAL ERROR\n", stderr);
  va_copy(args1, args);
  ::std::vfprintf(stderr, format, args1);

  ::std::fputs("controve FATAL ERROR see stderr\n", stdout);

  const std::string filename = getFilename();
  if (!filename.empty()) {
    FILE *errorfile = ::std::fopen(filename.c_str(), "w");
    if (errorfile != NULL) {
      va_copy(args2, args);
      vfprintf(errorfile, format, args2);
      fclose(errorfile);
    } else {
      fprintf(stderr, "controve fatal error: fopen('%s', \"w\")"
          " failed with %d\n", filename.c_str(), errno);
    }
  }

  abort();
}

}  // namespace controve

#include "third_party/gflags/include/gflags/gflags.h"

DEFINE_uint64(print, 0, "Print logging values or whatever");

int main() {
    return FLAGS_print;
}

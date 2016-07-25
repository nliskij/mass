#include <cstdlib>

int main() {
    void *big_chunk = std::malloc(999999);
    std::free(big_chunk);
}

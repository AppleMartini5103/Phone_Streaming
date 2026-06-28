#include <cstdio>
#include "streamcore/types.hpp"
#include "streamcore/bufferPool.hpp"

int main() {
    using namespace streamcore;
    std::printf("link OK: %s\n", version());

    BufferPool pool(2, 1024);
    std::printf("start = %zu\n", pool.available());
    {
        auto a = pool.acquire();
        auto b = pool.acquire();
        std::printf("borrowed = %zu\n", pool.available());
        auto c = pool.acquire();
        std::printf("c = %s\n", c ? "valid" : "null");
    }
    
    std::printf("returned = %zu\n", pool.available());
    return 0;
}
#include <cstdio>
#include "streamcore/types.hpp"

int main() {
    using namespace streamcore;
    std::printf("link OK: %s\n", version());

    RawVideoFrame f;
    f.width = 1280; f.height = 720; f.pts_us = 33333;
    std::printf("RawVideoFrame %dx%d pts=%lldus data=%s\n",
                f.width, f.height, (long long)f.pts_us,
                f.data ? "set" : "null");
    return 0;
}
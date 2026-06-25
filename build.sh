#!/usr/bin/env bash
set -e

if [ -d build ]; then
    rm -rf build
fi

cmake -S . -B build -G Ninja
cmake --build build -j4

./build/hello
#!/bin/bash

scriptDirectory="$(cd "$(dirname "${BASH_SOURCE[0]}")" > /dev/null 2>&1 && pwd)"

CC=clang-11 CXX=clang++-11 cmake --build "${scriptDirectory}/../generated" --target install

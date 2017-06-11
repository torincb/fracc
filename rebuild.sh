#!/bin/bash

mkdir -p build
cd build
rm -rf *
CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Debug ..

if [ "$1" == "-b" ]; then
    make
fi

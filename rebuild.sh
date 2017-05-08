#!/bin/bash

mkdir -p build
cd build
rm -rf *
CC=clang CXX=clang++ cmake ..

if [ "$1" == "-b" ]; then
    make
fi

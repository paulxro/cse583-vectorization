#!/bin/bash

cd ~/proj

rm -rf ./build && mkdir build && cd build
cmake ..
make

mkdir -p ../tests/llvm
mkdir -p ../tests/viz

CLANG_DEBUG_OPTS=""

clang -emit-llvm -S $CLANG_DEBUG_OPTS ../tests/$1.c -Xclang -disable-O0-optnone -o ../tests/llvm/$1.ll

opt -disable-output -passes="dot-cfg" ../tests/llvm/$1.ll
cat .cloned_fn.dot | dot -Tpdf > ../tests/viz/$1.pdf

rm -f .*.dot

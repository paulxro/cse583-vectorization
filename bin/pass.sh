#!/bin/bash

cd ~/proj

rm -rf ./build && mkdir build && cd build
cmake ..
make

mkdir -p ../tests/llvm
mkdir -p ../tests/viz

clang -emit-llvm -S ../tests/$1.c -Xclang -disable-O0-optnone -o ../tests/llvm/$1.ll
opt -disable-output -load-pass-plugin=./LoopInversionPass/LoopInversionPass.so -passes="loop-inverter-improved" ../tests/llvm/$1.ll
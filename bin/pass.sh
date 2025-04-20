#!/bin/bash

cd ~/proj

rm -rf ./build && mkdir build && cd build
cmake ..
make

mkdir -p ../tests/llvm
mkdir -p ../tests/viz

PASS_NAME="loop-inverter-improved"

CLANG_DEBUG_OPTS=""
OPT_DEBUG_OPTS=""

clang -emit-llvm -S $CLANG_DEBUG_OPTS ../tests/$1.c -Xclang -disable-O0-optnone -o ../tests/llvm/$1.ll
opt -disable-output -load-pass-plugin=./LoopInversionPass/LoopInversionPass.so $OPT_DEBUG_OPTS -passes=$PASS_NAME ../tests/llvm/$1.ll
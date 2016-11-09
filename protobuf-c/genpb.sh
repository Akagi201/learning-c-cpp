#!/usr/bin/env bash

cd proto

echo "generate protobuf C code..."

protoc-c --c_out=../mpb *.proto

clang-format -sort-includes -style=Google -i ../mpb/*.c ../mpb/*.h

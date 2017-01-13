#!/usr/bin/env bash

echo "clang-tidy starting "$*" ..."

sleep 1

TIDY="clang-tidy"

if [ -f /usr/local/opt/llvm/bin/clang-tidy ]; then
    TIDY="/usr/local/opt/llvm/bin/clang-tidy"
fi

FORMAT="clang-format"

if [ -f /usr/local/bin/clang-format ]; then
    FORMAT="/usr/local/bin/clang-format"
fi

$TIDY \
    -fix \
    -fix-errors \
    -header-filter=.* \
    --checks=readability-braces-around-statements,misc-macro-parentheses \
    $* \
    -- -I.

echo "clang-tidy finished!"

echo "clang-format starting "$*" ..."

sleep 1

$FORMAT -sort-includes -i $*

echo "clang-format finished!"


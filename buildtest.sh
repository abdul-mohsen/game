#!/bin/bash
set -ex
clear
clang -Wall -Wextra -o test test.c 
echo done
./test

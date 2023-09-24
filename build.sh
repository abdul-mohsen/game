#!/bin/bash
set -ex

clang -Wall -Wextra -o build/main main.c -lglfw -lm -lXrandr -lXi -lXxf86vm -lpthread -lX11 -ldl -lXinerama -lXcursor
echo done
./main

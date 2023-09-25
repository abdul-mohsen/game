#!/bin/bash
set -ex
rm -rf build
mkdir build
clang -Wall -Wextra -o build/main main.c -lglfw -lm -lXrandr -lXi -lXxf86vm -lpthread -lX11 -ldl -lXinerama -lXcursor -lGL -lglut -lGLEW
echo done
./build/main

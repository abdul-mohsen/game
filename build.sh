#!/bin/bash
set -ex
clear
rm -rf build
mkdir build
clang -O3 -Wall -Wextra -o build/main main.c lib/*.c \
	-lglfw -lm -lXrandr -lXi -lXxf86vm -lpthread -lX11 -ldl -lXinerama \
	-lXcursor -lGL -lglut -lGLEW -g -v 
echo done
./build/main

#pragma once

#include "Array.h"
typedef Array ArrayPointer;

ArrayPointer * initArrayPointer(const unsigned int elementSize);
ArrayPointer * _initArrayPointer(const unsigned int elementSize, const unsigned int capacity);
int addItemPointer(ArrayPointer * array, const unsigned int item);
int freeArrayPointer(ArrayPointer * array);

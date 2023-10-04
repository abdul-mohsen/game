#pragma once

typedef struct {
   void *data;
   unsigned int elementSize;
   unsigned int size;
   unsigned int capacity;
} Array;


Array * initArray(const unsigned int elementSize);
Array * _initArray(const unsigned int elementSize, const unsigned int capacity);
int addItem(Array * array, void * item);
int freeArray(Array * array);

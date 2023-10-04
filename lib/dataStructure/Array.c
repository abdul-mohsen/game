#include "Array.h"
#include <stdlib.h>
#include <string.h>

Array * initArray(const unsigned int elementSize) {
  return _initArray(elementSize, 10);
}

Array * _initArray(const unsigned int elementSize, const unsigned int capacity) {
  Array * array = malloc(sizeof(Array));
  array->size = 0;
  array->elementSize = elementSize;
  array->capacity = capacity;
  array->data= malloc(sizeof(elementSize) * capacity);
  return array;
}

int addItem(Array * array, void * item) {
  if (array->size > array->capacity) {
    return EXIT_FAILURE;
  }

  if (array->size == array->capacity) {
    /* Need to handle this case
     */
    return EXIT_FAILURE;
  }
  memcpy(array->data + (array->size) * (array->elementSize), item, array->elementSize);
  array->size++;
  return EXIT_SUCCESS;
}

int freeArray(Array * array) {
  free(array);
  return EXIT_SUCCESS;
}

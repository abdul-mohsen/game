#pragma once

/* TODO 
 * This array should have dynaic size for each elment
*/
typedef struct {
   unsigned int elementSize;
   void *data;
} DynamicItem;

typedef struct {
   DynamicItem *data;
   int size;
   int capacity;
} DynamicArray;


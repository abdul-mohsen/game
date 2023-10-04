#pragma once

struct LinkedList {
   void *data;
   unsigned int elementSize;
   struct LinkedList * next;
};


struct LinkedList * initLinkedList();
struct LinkedList * addNode(struct LinkedList * head, void * item, const unsigned int itemSize);
int freeLinkedList(struct LinkedList * array);

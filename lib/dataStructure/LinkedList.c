#include "LinkedList.h"
#include <stdlib.h>

struct LinkedList * addNode(struct LinkedList * head, void * item, const unsigned int itemSize) {
  struct LinkedList * node = malloc(sizeof(struct LinkedList));
  node->data = item;
  node->elementSize = itemSize;
  if (head == NULL) {
    head = node;
  } else {
    node->next = head;
  }
  return node;
}


int freeLinkedList(struct LinkedList * array) {
  struct LinkedList * node;
  struct LinkedList * next;
  
  while (next != NULL) {
    node = next;
    next = node->next;
    free(node);
  }

  return EXIT_SUCCESS;
}

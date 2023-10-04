#include "VertexBuffer.h"
#include "VertexArray.h"
#include "../dataStructure/LinkedList.h"
#include "VertexBufferLayout.h"
#include <GL/glew.h>
#include <stdlib.h>
#include "../util/Util.h"

struct VertexArray * createVertexArray() {
  struct VertexArray * vao = malloc(sizeof(struct VertexArray));
  glGenVertexArrays(1, &vao->renderId);
  return vao;
}

void bindVertexArray(struct VertexArray * self) {
  glBindVertexArray(self->renderId);
}

void unbindVertexArray(struct VertexArray * self) {
  glBindVertexArray(0);
}

void deleteVertexArray(struct VertexArray * self) {
  glDeleteVertexArrays(1, &self->renderId);
}

void addBuffer(struct VertexArray * self, const VertexBuffer vb, const struct VertexBufferLayout layout) {
  bindVertexArray(self);
  bindVertexBuffer(&vb);
  struct LinkedList * node = layout.head;
  unsigned int i = 0;
  void * offset = 0;

  do {
    struct VertexBufferElement * elm = node->data;
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, elm->count, elm->type, elm->normalized, layout.stride, offset);
    offset += elm->count * elm->size;
    i++;
  } while ((node = node->next) != NULL);
}

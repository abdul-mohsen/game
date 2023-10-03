#include "IndexBuffer.h"
#include <GL/glew.h>
#include <stdlib.h>

IndexBuffer * createIndexBuffer(const unsigned int* data, unsigned int count) {
  IndexBuffer *indexBuffer = malloc(sizeof(IndexBuffer));
  indexBuffer->count = count;
  indexBuffer->renderId = 0;
  unsigned int buffer = indexBuffer->renderId;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->renderId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
  return indexBuffer;
}

void deleteIndexBuffer(const IndexBuffer * indexBuffer){
  glDeleteBuffers(1, &indexBuffer->renderId);
}

void bindIndexBuffer(const IndexBuffer * indexBuffer){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->renderId);
}

void unbindIndexBuffer(const IndexBuffer * indexBuffer){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

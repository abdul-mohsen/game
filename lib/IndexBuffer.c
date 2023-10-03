#include "IndexBuffer.h"
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

IndexBuffer * createIndexBuffer(const unsigned int* data, unsigned int count) {
  IndexBuffer *indexBuffer = malloc(sizeof(IndexBuffer));
  indexBuffer->count = count;
  glGenBuffers(1, &indexBuffer->renderId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->renderId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
  return indexBuffer;
}

void deleteIndexBuffer(const IndexBuffer * indexBuffer){
  glDeleteBuffers(1, &indexBuffer->renderId);
}

void bindIndexBuffer(IndexBuffer * indexBuffer) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->renderId);
}

void unbindIndexBuffer() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

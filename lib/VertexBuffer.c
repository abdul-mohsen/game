#pragma once

#include "VertexBuffer.h"
#include <GL/glew.h>
#include <stdlib.h>

VertexBuffer * createVertexBuffer(const void* data, unsigned int size){
  VertexBuffer * vertexBuffer = malloc(sizeof(VertexBuffer));
  vertexBuffer->renderId = 1;
  unsigned int buffer = vertexBuffer->renderId;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  return vertexBuffer;
}

void deleteVertexBuffer(const VertexBuffer * vertexBuffer) {
  glDeleteBuffers(1, &vertexBuffer->renderId);
}

void bindVertexBuffer(const VertexBuffer * vertexBuffer) {
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->renderId);
}

void unbindVertexBuffer(const VertexBuffer * vertexBuffer) {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

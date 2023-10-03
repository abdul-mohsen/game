#pragma once

typedef struct {
  unsigned int renderId;
} VertexBuffer;

VertexBuffer * createVertexBuffer(const void* data, unsigned int size);
void deleteVertexBuffer(const VertexBuffer * vertexBuffer);
void bindVertexBuffer(const VertexBuffer * vertexBuffer);
void unbindVertexBuffer(const VertexBuffer * vertexBuffer);

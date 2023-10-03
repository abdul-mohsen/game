#pragma once

typedef struct {
  unsigned int renderId;
  unsigned int count;
} IndexBuffer;

IndexBuffer * createIndexBuffer(const unsigned int* data, unsigned int count);
void deleteIndexBuffer(const IndexBuffer * vertexBuffer);
void bindIndexBuffer(IndexBuffer * vertexBuffer);
void unbindIndexBuffer();

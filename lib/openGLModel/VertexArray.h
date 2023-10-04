#pragma ocne

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

struct VertexArray {
  unsigned int renderId;
};

struct VertexArray * createVertexArray();
void deleteVertexArray(struct VertexArray * self);
void bindVertexArray(struct VertexArray * self);
void unbindVertexArray(struct VertexArray * self);
void addBuffer(struct VertexArray * self, const VertexBuffer vb, const struct VertexBufferLayout layout);

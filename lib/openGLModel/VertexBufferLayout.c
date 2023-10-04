#include "VertexBufferLayout.h"
#include "../dataStructure/LinkedList.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

struct VertexBufferLayout * createVertexBufferLayout() {
  struct VertexBufferLayout * layout = malloc(sizeof(struct VertexBufferLayout));
  layout->head=NULL;
  layout->stride=0;
  return layout;
}

void pushVertexFufferElement(struct VertexBufferLayout * self, struct VertexBufferElement *vbe) {

  self->stride += vbe->size * vbe->count;
  self->head = addNode(self->head, vbe, vbe->size);
}

struct VertexBufferElement * createVertexBufferElement(
  unsigned int type,
  unsigned int size,
  int normalized,
  unsigned int count
) {
  struct VertexBufferElement *vbe = malloc(sizeof(struct VertexBufferElement));
  vbe->type = type;
  vbe->size = size;
  vbe->normalized = normalized;
  vbe->count = count;
  return vbe;
}

void pushVertexFufferElementUint(struct VertexBufferLayout * self, unsigned int count) {
  pushVertexFufferElement(self, createVertexBufferElement(GL_UNSIGNED_INT, sizeof(GLuint), GL_FALSE, count));
}

void pushVertexFufferElementFloat(struct VertexBufferLayout * self, unsigned int count) {
  pushVertexFufferElement(self, createVertexBufferElement(GL_FLOAT, sizeof(GLfloat), GL_FALSE, count));
}

void pushVertexFufferElementChar(struct VertexBufferLayout * self, unsigned int count) {
  pushVertexFufferElement(self, createVertexBufferElement(GL_UNSIGNED_BYTE, sizeof(GLbyte), GL_TRUE, count));
}

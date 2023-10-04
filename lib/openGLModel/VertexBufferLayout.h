#pragma once

struct VertexBufferElement{
  unsigned int type;
  unsigned int count;
  unsigned int size;
  int normalized;
};

struct VertexBufferLayout {
  struct LinkedList * head;
  unsigned int stride;
};
 
struct VertexBufferLayout * createVertexBufferLayout();
void pushVertexFufferElement(struct VertexBufferLayout * self, struct VertexBufferElement *vbe);
void pushVertexFufferElementUint(struct VertexBufferLayout * self, unsigned int count);
void pushVertexFufferElementFloat(struct VertexBufferLayout * self, unsigned int count);
void pushVertexFufferElementChar(struct VertexBufferLayout * self, unsigned int count);

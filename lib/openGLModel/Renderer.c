#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

void glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  printf("\n %d %d %d %d %d %s", source, type, id, severity, length, message);
}

void clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void draw(struct VertexArray * va, IndexBuffer * ib, struct Shader * shader) {

    bindVertexArray(va);
    bindIndexBuffer(ib);

    glDrawElements(GL_TRIANGLES, ib->count, GL_UNSIGNED_INT, NULL);
}

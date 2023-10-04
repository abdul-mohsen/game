#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib/openGLModel/IndexBuffer.h"
#include "lib/openGLModel/Shader.h"
#include "lib/openGLModel/VertexBuffer.h"
#include "lib/openGLModel/VertexArray.h"
#include "lib/openGLModel/VertexBufferLayout.h"
#include "lib/util/Util.h"
#define GLFW_DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define IMG_WIDTH 900
#define IMG_HEIGHT 600
#define TRUE 1
#define FALSE 0

//static void error_callback(int error, const char* description) {
//  fprintf(stderr, "Error: %s\n", description);
//}


static void glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  printf("\n %d %d %d %d %d %s", source, type, id, severity, length, message);
}


int main() {
  printf("\n------- Program Start -------\n");

  // glfwSetErrorCallback(error_callback);
  const void* userPrama = "";

  if (!glfwInit()) {

    printf("failed to init\n");
    return EXIT_FAILURE;

  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(IMG_WIDTH, IMG_HEIGHT, "ssda", NULL, NULL);

  if (!window) {
    printf("no Window\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (glewInit()) {
    printf("failed to init glew\n");
  }
  GLClearError();
  glDebugMessageCallback(glErrorCallback, userPrama);
  GLCheckError();

  float positions[] = {
    .5f, -.5f,
    .5f, .5f,
    -.5f, -.5f,
    -.5f, .5f,
  };

  unsigned int indices[] = {
    0,1,2, 
    1,2,3
  };

  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  struct VertexArray * va = createVertexArray();

  VertexBuffer *vertexBuffer = createVertexBuffer(positions, 4 * 2 * sizeof(float));

  struct VertexBufferLayout * layout = createVertexBufferLayout();
  pushVertexFufferElementFloat(layout, 2);
  addBuffer(va, *vertexBuffer, *layout);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

  IndexBuffer * indexBuffer = createIndexBuffer(indices, 6);

  struct Shader * shader = initShader("res/shaders/Basic.shader");
  struct _Shader *mShader = parseShader(shader);
  unsigned int iShader = createShader(shader, mShader->vertex, mShader->fragment);
  glUseProgram(iShader);

  int location = glGetUniformLocation(iShader, "u_Color");
  glUniform4f(location, .2f, .3f, .8f, 1.0f);

  glBindVertexArray(0);
  glUseProgram(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  float r = .0f;
  float increament = .05f;

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(iShader);
    glUniform4f(location, r, .3f, .8f, 1.0f);

    bindVertexArray(va);
    bindIndexBuffer(indexBuffer);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    if (r > 1.0f) increament = -.05f;
    else if (r < .05f) increament = .05f;

    r += increament;

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  free(vertexBuffer);
  free(indexBuffer);
  glfwTerminate();
  
  printf("\n");
  return EXIT_SUCCESS;
}

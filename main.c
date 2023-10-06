#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib/openGLModel/IndexBuffer.h"
#include "lib/openGLModel/Renderer.h"
#include "lib/openGLModel/Shader.h"
#include "lib/openGLModel/VertexBuffer.h"
#include "lib/openGLModel/VertexArray.h"
#include "lib/openGLModel/VertexBufferLayout.h"
#include "lib/util/Util.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define IMG_WIDTH 900
#define IMG_HEIGHT 600
#define TRUE 1
#define FALSE 0



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
  bindShader(shader);
  setUniform4fShader(shader, "u_Color", .2f, .3f, .8f, 1.0f);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  unbindVertexArray(va);
  unbindVertexBuffer();
  unbindIndexBuffer();
  unbindShader(shader);

  float r = .0f;
  float increament = .05f;

  struct Renderer * renderer = malloc(sizeof(struct Renderer));

  while (!glfwWindowShouldClose(window)) {

    bindShader(shader);
    setUniform4fShader(shader, "u_Color", r, .3f, .8f, 1.0f);
    draw(va, indexBuffer, shader);

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

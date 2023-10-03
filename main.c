#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib/Util.c"
#include "lib/VertexBuffer.c"
#include "lib/IndexBuffer.c"
#include "lib/VertexBuffer.h"
#define GLFW_DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define IMG_WIDTH 900
#define IMG_HEIGHT 600
#define TRUE 1
#define FALSE 0

static const struct
{
  float x, y;
  float r, g, b;
} vertces[3] = 
  {
    { -.6f, -.4f, 1.f, 0.f, 0.f},
    { .6f, -.4f, 0.f, 1.f, 0.f},
    { 0.f, -.6f, 0.f, 0.f, 1.f},
  };

struct Shader {
  char* vertex;
  char* fragment;
};

struct Shader * parseShader(char* fileName) {
  char* text = readFile(fileName);
  char* origin = text;
  char* loc = NULL;
  int iter = 0;
  struct Shader *mShader = malloc(sizeof(struct Shader));

  while ((loc = strchr(text, '#')) != NULL) {
    text = loc;
    if (++iter == 1) {
      int size = strchr(text + 1, '#') - text;
      mShader->vertex = malloc(size);
      memcpy(mShader->vertex, text, size);
      mShader->vertex[size - 1] = '\0';

    } else if(iter == 2) {
      int size = strchr(text + 1, '\0') - text;
      mShader->fragment = malloc(size);
      memcpy(mShader->fragment, text, size);
      mShader->fragment[size - 1] = '\0';
    }
    text++;
  }

  free(origin);
  return mShader;
}

static void error_callback(int error, const char* description)

{
  fprintf(stderr, "Error: %s\n", description);
}

static unsigned int CompileShader(unsigned int type, const char* source) {

  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*) alloca(length * sizeof(char));

    glGetShaderInfoLog(id, length, &length, message);
    printf("Fail to compile shader\n");
    if (type == GL_VERTEX_SHADER) {
      printf("vertex \n");
    } else if (type == GL_FRAGMENT_SHADER) {
      printf("fragment \n");
    } else {
      printf("Unkown error %d", type);
    } 
    glDeleteProgram(id);
    return EXIT_SUCCESS;
  
  }
  
  return id;
}

static unsigned int CreateShader(const char* vertexShader, const char* fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;

}
static void glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
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

  VertexBuffer *vertexBuffer = createVertexBuffer(positions, 4 * 2 * sizeof(float));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

  IndexBuffer * indexBuffer = createIndexBuffer(indices, 6);

  struct Shader *mShader = parseShader("res/shaders/Basic.shader");
  unsigned int shader = CreateShader(mShader->vertex, mShader->fragment);
  glUseProgram(shader);

  int location = glGetUniformLocation(shader, "u_Color");
  glUniform4f(location, .2f, .3f, .8f, 1.0f);

  glBindVertexArray(0);
  glUseProgram(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  float r = .0f;
  float increament = .05f;

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glUniform4f(location, r, .3f, .8f, 1.0f);

    glBindVertexArray(vao);
    bindIndexBuffer(indexBuffer);
    GLCheckError();

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

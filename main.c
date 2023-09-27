#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GLFW_DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define IMG_WIDTH 900
#define IMG_HEIGHT 600

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
static void debug(char* msg) {
  printf("%s\n", msg);
}

static void debugInt(int x) {
  printf("%d\n", x);
}

static char* readFile(const char* file) {
  FILE *handler = fopen(file, "r");
  char *buffer = NULL;
  int stringSize, readSize;

  if (handler) {
    fseeko(handler, 0, SEEK_END);
    stringSize = ftello(handler);

    rewind(handler);
    buffer = (char*) malloc(sizeof(char) * (stringSize + 1));
    readSize = fread(buffer, sizeof(char), stringSize, handler);

    buffer[stringSize] = '\0';

    if (stringSize != readSize) {
      free(buffer);
      buffer = NULL;
    }

    fclose(handler);
  
  }

  return buffer;
}

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

int main()
{
  printf("\n------- Program Start -------\n");

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {

    printf("failed to init\n");
    return EXIT_FAILURE;

  }

  GLFWwindow* window = glfwCreateWindow(IMG_WIDTH, IMG_HEIGHT, "ssda", NULL, NULL);

  if (!window) {
    printf("no Window\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);

  if (glewInit()) {
    printf("failed to init glew\n");
  }

  float positions[6] = {
    -.5f, -.5f,
    .0f, .5f,
    .5f, -.5f,
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

  struct Shader *mShader = parseShader("res/shaders/Basic.shader");
  unsigned int shader = CreateShader(mShader->vertex, mShader->fragment);
  glUseProgram(shader);


  while (!glfwWindowShouldClose(window)) {
     glClear(GL_COLOR_BUFFER_BIT);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glfwTerminate();
  
  printf("\n");
  return EXIT_SUCCESS;
}

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
    printf("Fail to compile shader");
    if (type == GL_VERTEX_SHADER) {
      printf("vertex \n");
    } else if (type == GL_FRAGMENT_SHADER) {
      printf("fragment \n");
    } else {
      printf("Unkown error %d", type);
    } 
    glDeleteShader(id);
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
  printf("\n");

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {

    printf("failed to init");
    return EXIT_FAILURE;

  }

  GLFWwindow* window = glfwCreateWindow(IMG_WIDTH, IMG_HEIGHT, "ssda", NULL, NULL);

  if (!window) {
    printf("no Window");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);

  if (glewInit()) {
    printf("failed to init glew");
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

  char* vertexShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;"
    "\n"
    "void main()\n"
    "{\n"
    " gl_Position = position;\n"
    "\n}"
  ;

  char* fragmentShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color;\n"
    "\n"
    "void main()\n"
    "{\n"
    " color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "\n}"
  ;

  unsigned int shader = CreateShader(vertexShader, fragmentShader);
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

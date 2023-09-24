#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define GLFW_DLL
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

int main()
{
  printf("ssda new run");

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

  while (!glfwWindowShouldClose(window)) {
    // glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glfwTerminate();
  
  return EXIT_SUCCESS;
}

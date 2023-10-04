#include "Util.h"
#include <utils.h>
#include <stdio.h>
#include <GL/glew.h>

void debug(char* msg) {
  printf("%s\n", msg);
}

void debugInt(int x) {
  printf("%d\n", x);
}
void debugFloat(float msg) {
  printf("%f\n", msg);
}

void GLClearError() {
  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR) {
    printf("\nopenGL Error: %d",error);
  } 
}

void GLCheckError() {
  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR) {
    printf("\nopenGL Error: 0x%02X",error);
    printf("\nopenGL Error: %d",error);
  } 
}

char* readFile(const char* file) {
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

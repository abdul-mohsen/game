#include "Shader.h"
#include "../util/Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>


int compileShader(unsigned int type, const char * source) {
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

struct _Shader * parseShader(struct Shader * self) {
  char * fileName = self->filePath;
  char* text = readFile(fileName);
  char* origin = text;
  char* loc = NULL;
  int iter = 0;
  struct _Shader *mShader = malloc(sizeof(struct _Shader));

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

unsigned int createShader(struct Shader * self, const char* vertexShader, const char* fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;

}

struct Shader * initShader(char * filePath) {
  struct Shader * shader = malloc(sizeof(struct Shader));
  shader->filePath = filePath;
  shader->renderId = 0;
  return shader;
}

void bindShader(struct Shader * self) {

}
void unbindShader(struct Shader * self);
void SetUniform4fShader(struct Shader * self, const char * name, float v0, float v1, float v2, float v3);


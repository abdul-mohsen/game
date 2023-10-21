#pragma once

struct Shader {
  unsigned int renderId;
  char * filePath;
};

struct _Shader {
  char* vertex;
  char* fragment;
};

struct Shader * initShader(char * filePath);
void bindShader(struct Shader * self);
void unbindShader(struct Shader * self);
void setUniform4fShader(struct Shader * self, const char * name, float v0, float v1, float v2, float v3);
int getUniform4fShader(struct Shader * self, const char * name); 
void GLClearError();
void GLCheckError();

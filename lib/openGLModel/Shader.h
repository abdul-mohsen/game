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
void SetUniform4fShader(struct Shader * self, const char * name, float v0, float v1, float v2, float v3);

struct _Shader * parseShader(struct Shader * self);
unsigned int createShader(struct Shader * self, const char* vertexShader, const char* fragmentShader);

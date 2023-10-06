#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

struct Renderer {};

void error_callback(int error, const char* description);

void glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

void clear();

void draw(struct VertexArray * va, IndexBuffer * ib, struct Shader * shader);


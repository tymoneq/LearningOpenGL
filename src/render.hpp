#pragma once
#include "indexBuffer.hpp"
#include "shader.hpp"
#include "vertexArray.hpp"
#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <alloca.h>

#define ASSERT(x)                                                              \
  do {                                                                         \
    if (!(x)) {                                                                \
      __builtin_trap();                                                        \
    }                                                                          \
  } while (0)

#define GLCall(x)                                                              \
  do {                                                                         \
    GLClearError();                                                            \
    x;                                                                         \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));                                 \
  } while (0)

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer {

public:
  void Clear() const ;
  void Draw(const VertexArray &va, const IndexBuffer &ib,
            const Shader &shader) const;
};
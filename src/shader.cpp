#include "shader.hpp"
#include "render.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string &filePath)
    : filePath(filePath), m_RenderID(0) {

  ShaderProgramSource source = ParseShader(filePath);

  m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() { GLCall(glDeleteProgram(m_RenderID)); }

unsigned int Shader::CompileShader(const std::string &source,
                                   unsigned int type) {

  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);

    std::cerr << "FAILED TO COMPILE SHADER\n";
    std::cerr << message << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}

ShaderProgramSource Shader::ParseShader(const std::string &filePath) {

  std::ifstream stream(filePath);

  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  while (std::getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {

      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    } else
      ss[int(type)] << line << "\n";
  }

  return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CreateShader(const std::string &vertexShader,
                                  const std::string &fragmentShader) {

  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
  unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));
  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}

void Shader::Bind() const { GLCall(glUseProgram(m_RenderID)); }

void Shader::UnBind() const { GLCall(glUseProgram(0)); }

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3) {

  GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string &name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache.at(name);

  int location = glGetUniformLocation(m_RenderID, name.c_str());
  if (location == -1)
    std::cout << "location == -1" << std::endl;

  m_UniformLocationCache[name] = location;

  return location;
}
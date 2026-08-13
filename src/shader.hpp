#pragma once

#include <string>
struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
private:
  unsigned int m_RenderID;
  std::string filePath;

public:
  Shader(const std::string &filePath);
  ~Shader();

  void Bind() const;
  void UnBind() const;

  void SetUniform4f(const std::string &name, float v0, float v1, float v2,
                    float v3);

private:
  unsigned int CompileShader(const std::string &source, unsigned int type);
  int GetUniformLocation(const std::string &name);
  unsigned int CreateShader(const std::string &vertexShader,
                            const std::string &fragmentShader);
  ShaderProgramSource ParseShader(const std::string &filePath);
};
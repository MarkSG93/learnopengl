#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
  // program ID
  unsigned int ID;
  const char* vertexPath;
  const char* fragmentPath;

  // Constructor
  Shader(const char* vertexPath, const char* fragmentPath);

  // load the shaders from disk
  void loadShaders();

  // activate shader
  void use();

  // utility uniform methods
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setFloat4(const std::string &name, float a, float b, float c, float d) const;
private:
  void checkShaderSuccess(unsigned int shader, unsigned int shaderIv);

  unsigned int compileShader(const char *vertexShaderCode, unsigned int shaderType);

  void linkShaders(unsigned int vertex, unsigned int fragment);

  std::string readShaderFile(const std::string &path);
};

#endif

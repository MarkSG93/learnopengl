#include "shader.h"

void Shader::checkShaderSuccess(unsigned int shader, unsigned int shaderIv) {
  // Shader compilation success
  int  success;
  char infoLog[512];
  if (shaderIv == GL_LINK_STATUS)   {
    glGetProgramiv(shader, shaderIv, &success);
  } else {
    glGetShaderiv(shader, shaderIv, &success);
  }

  if(!success) {
    if (shaderIv != GL_LINK_STATUS) {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::COMPILATION\n" << infoLog << std::endl;
      return;
    }

    glGetProgramInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
  }
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  this->vertexPath = vertexPath;
  this->fragmentPath = fragmentPath;
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::loadShaders() {
  unsigned int vertex;
  unsigned int fragment;

  try {
    vertex = compileShader(readShaderFile(vertexPath).c_str(), GL_VERTEX_SHADER);
    fragment = compileShader(readShaderFile(fragmentPath).c_str(), GL_FRAGMENT_SHADER);
  } catch (std::ifstream::failure e) {
    std::cout << e.what() << std::endl;
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
  }

  linkShaders(vertex, fragment);

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

std::string Shader::readShaderFile(const std::string &path) {
  std::ifstream shaderFile;
  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  shaderFile.open(path);

  std::stringstream shaderStream;
  shaderStream << shaderFile.rdbuf();
  shaderFile.close();

  return shaderStream.str();
}

void Shader::linkShaders(unsigned int vertex, unsigned int fragment) {
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkShaderSuccess(ID, GL_LINK_STATUS);
}

unsigned int Shader::compileShader(const char *vertexShaderCode, unsigned int shaderType) {
  unsigned int shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &vertexShaderCode, NULL);
  glCompileShader(shader);
  checkShaderSuccess(shader, GL_COMPILE_STATUS);

  return shader;
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
 glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setFloat4(const std::string &name, float a, float b, float c, float d) const {
  glUniform4f(glGetUniformLocation(ID, name.c_str()), a, b, c, d);
}
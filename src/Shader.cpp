//
// Created by sohaibalam on 12/05/23.
//

#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "Logger.h"

namespace GL_UTILITY {

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  GLuint vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
  GLuint fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  GLint success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    UTILITIES::logger.log(UTILITIES::LogLevel::ERROR,
                          "Error creating Shader Program: " +
                              std::string(infoLog));
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

GLuint Shader::loadShader(const char *path, GLenum shaderType) {
  std::string shaderCode;
  std::ifstream shaderFile;
  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    shaderFile.open(path);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    shaderCode = shaderStream.str();
  } catch (std::ifstream::failure &e) {
    UTILITIES::logger.log(UTILITIES::LogLevel::ERROR,
                          "Error parsing shader: " + std::string(e.what()));
  }

  const char *shaderCodeCStr = shaderCode.c_str();
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderCodeCStr, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    UTILITIES::logger.log(UTILITIES::LogLevel::ERROR,
                          "Error creating Shader: " + std::string(infoLog));
  }

  return shader;
}

} // namespace GL_UTILITY
//
// Created by sohaibalam on 12/05/23.
//

#ifndef NAVIERSTOKES_SHADER_H
#define NAVIERSTOKES_SHADER_H

#include <glad/glad.h>
#include <string>

namespace GL_UTILITY {

class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);

  void useShader() const { glUseProgram(shaderProgram); }

  void setInt(const std::string &name, GLint value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
  }

  void setFloat(const std::string &name, GLfloat value) const {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
  }

private:
  static GLuint loadShader(const char *path, GLenum shaderType);

private:
  GLuint shaderProgram;
};

} // namespace GL_UTILITY

#endif // NAVIERSTOKES_SHADER_H

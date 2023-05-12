//
// Created by sohaibalam on 12/05/23.
//

#ifndef GLEN_VBO_H
#define GLEN_VBO_H

#include "glad/glad.h"
namespace GL_UTILITY {

class VBO {
public:
  // Reference ID of the Vertex Buffer Object
  GLuint ID;
  // Constructor that generates a Vertex Buffer Object and links it to vertices
  VBO(GLfloat *vertices, GLsizeiptr size);

  // Binds the VBO
  void Bind();
  // Unbinds the VBO
  void Unbind();
  // Deletes the VBO
  void Delete();
};

} // namespace GL_UTILITY

#endif // GLEN_VBO_H

//
// Created by sohaibalam on 12/05/23.
//

#ifndef GLEN_VAO_H
#define GLEN_VAO_H

#include "VBO.h"
#include "glad/glad.h"
namespace GL_UTILITY {

class VAO {
public:
  // ID reference for the Vertex Array Object
  GLuint ID;
  // Constructor that generates a VAO ID
  VAO();

  // Links a VBO Attribute such as a position or color to the VAO
  void LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type,
                  GLsizeiptr stride, void *offset);
  // Binds the VAO
  void Bind();
  // Unbinds the VAO
  void Unbind();
  // Deletes the VAO
  void Delete();
};

} // namespace GL_UTILITY

#endif // GLEN_VAO_H

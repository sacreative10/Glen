//
// Created by sohaibalam on 12/05/23.
//

#ifndef GLEN_EBO_H
#define GLEN_EBO_H

#include "glad/glad.h"
namespace GL_UTILITY {

class EBO {
public:
  // ID reference of Elements Buffer Object
  GLuint ID;
  // Constructor that generates a Elements Buffer Object and links it to indices
  EBO(GLuint *indices, GLsizeiptr size);

  // Binds the EBO
  void Bind();
  // Unbinds the EBO
  void Unbind();
  // Deletes the EBO
  void Delete();
};
}; // namespace GL_UTILITY

#endif // GLEN_EBO_H

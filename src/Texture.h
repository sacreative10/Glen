//
// Created by sohaibalam on 13/05/23.
//

#ifndef GLEN_TEXTURE_H
#define GLEN_TEXTURE_H

#include <glad/glad.h>

#include <stb/stb_image.h>

#include "Shader.h"

namespace GL_UTILITY {

class Texture {
public:
  GLuint ID;
  GLenum type;
  Texture(const char *image, GLenum texType, GLenum slot, GLenum format,
          GLenum pixelType);

  // Assigns a texture unit to a texture
  void texUnit(Shader &shader, const char *uniform, GLuint unit);
  // Binds a texture
  void Bind();
  // Unbinds a texture
  void Unbind();
  // Deletes a texture
  void Delete();
};

} // namespace GL_UTILITY

#endif // GLEN_TEXTURE_H

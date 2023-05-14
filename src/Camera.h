//
// Created by sohaibalam on 14/05/23.
//

#ifndef GLEN_CAMERA_H
#define GLEN_CAMERA_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/vec3.hpp>

using namespace GL_UTILITY;
namespace UTILITIES {

class Camera {
public:
  Camera(uint32_t width, uint32_t height, glm::vec3 position);

  void updateMatrices(float FOVdeg, float nearPlane, float farPlane,
                      Shader &shader);

  void handleInputs(GLFWwindow *window);

public:
  glm::vec3 m_position;
  glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

  bool firstClick = true;

  uint32_t m_width;
  uint32_t m_height;

  float m_speed = 0.1f;
  float m_sensitivity = 100.0f;
};

} // namespace UTILITIES

#endif // GLEN_CAMERA_H

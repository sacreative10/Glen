//
// Created by sohaibalam on 14/05/23.
//

#include "Camera.h"
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace UTILITIES {

Camera::Camera(uint32_t width, uint32_t height, glm::vec3 position)
    : m_width(width), m_height(height), m_position(position) {}

void Camera::updateMatrices(float FOVdeg, float nearPlane, float farPlane,
                            Shader &shader) {
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 proj = glm::mat4(1.0f);

  view = glm::lookAt(m_position, m_position + m_orientation, m_up);
  proj = glm::perspective(FOVdeg, (float)(m_width / m_height), nearPlane,
                          farPlane);
  glm::mat4 viewxproj = proj * view;
  shader.setMatrix4x4("camMatrix", glm::value_ptr(viewxproj));
}
void Camera::handleInputs(GLFWwindow *window) {

  // Handles key inputs
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    m_position += m_speed * m_orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    m_position += m_speed * -glm::normalize(glm::cross(m_orientation, m_up));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    m_position += m_speed * -m_orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    m_position += m_speed * glm::normalize(glm::cross(m_orientation, m_up));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    m_position += m_speed * m_up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    m_position += m_speed * -m_up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    m_speed = 0.4f;
  } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    m_speed = 0.1f;
  }

  // Handles mouse inputs
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    // Hides mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Prevents camera from jumping on the first click
    if (firstClick) {
      glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
      firstClick = false;
    }

    // Stores the coordinates of the cursor
    double mouseX;
    double mouseY;
    // Fetches the coordinates of the cursor
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Normalizes and shifts the coordinates of the cursor such that they begin
    // in the middle of the screen and then "transforms" them into degrees
    float rotX = m_sensitivity * (float)(mouseY - (m_height / 2)) / m_height;
    float rotY = m_sensitivity * (float)(mouseX - (m_width / 2)) / m_width;

    // Calculates upcoming vertical change in the Orientation
    glm::vec3 newOrientation =
        glm::rotate(m_orientation, glm::radians(-rotX),
                    glm::normalize(glm::cross(m_orientation, m_up)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, m_up) - glm::radians(90.0f)) <=
        glm::radians(85.0f)) {
      m_orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    m_orientation = glm::rotate(m_orientation, glm::radians(-rotY), m_up);

    // Sets mouse cursor to the middle of the screen so that it doesn't end up
    // roaming around
    glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    // Unhides cursor since camera is not looking around anymore
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // Makes sure the next time the camera looks around it doesn't jump
    firstClick = true;
  }
}
} // namespace UTILITIES
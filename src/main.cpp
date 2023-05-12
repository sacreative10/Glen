#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "EBO.h"
#include "Logger.h"
#include "Shader.h"
#include "VAO.h"

const int OPENGL_MAJOR_VERSION = 4;
const int OPENGL_MINOR_VERSION = 6;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

#include <cmath>

// Vertices coordinates
GLfloat vertices[] = {
    //               COORDINATES                  /     COLORS           //
    -0.5f,  -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f,
    0.02f, // Lower left corner
    0.5f,   -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f,
    0.02f, // Lower right corner
    0.0f,   0.5f * float(sqrt(3)) * 2 / 3,  0.0f, 1.0f, 0.6f,
    0.32f, // Upper corner
    -0.25f, 0.5f * float(sqrt(3)) * 1 / 6,  0.0f, 0.9f, 0.45f,
    0.17f, // Inner left
    0.25f,  0.5f * float(sqrt(3)) * 1 / 6,  0.0f, 0.9f, 0.45f,
    0.17f, // Inner right
    0.0f,   -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f,
    0.02f // Inner down
};

// Indices for vertices order
GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1  // Upper triangle
};

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLEN", NULL, NULL);
  // Error check if the window fails to create
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Introduce the window into the current context
  glfwMakeContextCurrent(window);

  // Load GLAD so it configures OpenGL
  gladLoadGL();
  // Specify the viewport of OpenGL in the Window
  // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
  glViewport(0, 0, 800, 800);

  GL_UTILITY::Shader shader("shaders/default.vert", "shaders/default.frag");

  GL_UTILITY::VAO VAO1;
  VAO1.Bind();

  GL_UTILITY::VBO VBO1(vertices, sizeof(vertices));
  GL_UTILITY::EBO EBO1(indices, sizeof(indices));

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float),
                  (void *)(3 * sizeof(float)));
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.useShader();

    shader.setFloat("scale", 0.5f);

    VAO1.Bind();

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();

  glfwDestroyWindow(window);

  glfwTerminate();
  return 0;
}
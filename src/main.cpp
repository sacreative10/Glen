#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "Camera.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"

const int OPENGL_MAJOR_VERSION = 4;
const int OPENGL_MINOR_VERSION = 6;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

#include <filesystem>

// Vertices coordinates
GLfloat vertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f, 0.0f,  0.0f,  -0.5f, 0.0f,
    -0.5f, 0.83f, 0.70f, 0.44f, 5.0f,  0.0f,  0.5f,  0.0f,  -0.5f, 0.83f,
    0.70f, 0.44f, 0.0f,  0.0f,  0.5f,  0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
    5.0f,  0.0f,  0.0f,  0.8f,  0.0f,  0.92f, 0.86f, 0.76f, 2.5f,  5.0f};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLEN", nullptr, nullptr);
  // Error check if the window fails to create
  if (window == nullptr) {
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

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)nullptr);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float),
                  (void *)(3 * sizeof(float)));
  VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
                  (void *)(6 * sizeof(float)));

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  std::string parentDir =
      (std::filesystem::current_path().std::filesystem::path::parent_path())
          .string();
  std::string texPath = "/Resources/";
  GL_UTILITY::Texture popCat((parentDir + texPath + "brick.png").c_str(),
                             GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA,
                             GL_UNSIGNED_BYTE);
  popCat.texUnit(shader, "tex0", 0);

  glEnable(GL_DEPTH_TEST);

  UTILITIES::Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.useShader();

    popCat.Bind();

    VAO1.Bind();

    camera.handleInputs(window);
    camera.updateMatrices(45.0f, 0.1f, 100.f, shader);

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT,
                   0);

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

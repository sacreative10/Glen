#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

#include "EBO.h"
#include "Logger.h"
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"

const int OPENGL_MAJOR_VERSION = 4;
const int OPENGL_MINOR_VERSION = 6;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

#include <cmath>
#include <filesystem>

// Vertices coordinates
GLfloat vertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper left corner
    0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Upper right corner
    0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] = {
    0, 2, 1, // Upper triangle
    0, 3, 2  // Lower triangle
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

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
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
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.useShader();

    shader.setFloat("scale", 0.5f);

    popCat.Bind();

    VAO1.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(vertices) / sizeof(vertices[0]),
                   GL_UNSIGNED_INT, 0);

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

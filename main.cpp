#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shaders/shader.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void printErrorCode(int code, const char* description) {
  std::cout << code << std::endl;
}

void initWindowHints() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // something for OSX
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use the new OpenGL
}

void processInput(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void render(GLFWwindow* window, Shader shader, unsigned int vao, unsigned ebo) {
  // Input
  processInput(window);

  // rendering commands
  glClearColor(0.2f, 0.8f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  shader.use();

  // Update uniform color
  float timeValue = glfwGetTime();
  float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
  shader.setFloat4("ourColor", 0.5f, greenValue, 0.2f, 1.0f);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  // check and call events and swap the buffers
  glfwPollEvents();
  glfwSwapBuffers(window);
}

void checkShaderSuccess(unsigned int shader, unsigned int shaderIv) {
  // Shader compilation success
  int  success;
  char infoLog[512];
  glGetShaderiv(shader, shaderIv, &success);

  if(!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

int main() {
  glfwInit();
  glfwSetErrorCallback(printErrorCode);
  initWindowHints();

  GLFWwindow* window = glfwCreateWindow(1024, 768, "Creating an OpenGL window", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window" << std::endl;
    return -1;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Resizing a window callback
  // Gets called on first load as well
  glViewport(0, 0, 1024, 768);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  float vertices[] = {
    0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top middle
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // bottom left
  };
  unsigned int indices[] = {
    0, 1, 2, // first triangle
//    1, 2, 3, // second triangle
  };

  // Vertex Array Objects
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Vertex Buffer Objects
  unsigned int VBO;
  glGenBuffers(1, &VBO); // Generate a buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer to GL_ARRAY_BUFFER target
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Transfer data into the currently bound buffer
  // Set the vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);
  //color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Element Buffer Object
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  Shader shader("/Users/mark.griffiths/projects/open-gl/learnopengl/shaders/vertexshader.glsl", "/Users/mark.griffiths/projects/open-gl/learnopengl/shaders/fragmentshader.glsl");
  shader.loadShaders();
  // Render loop
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while(!glfwWindowShouldClose(window)) {
    render(window, shader, VAO, EBO);
  }

  glfwTerminate();
  return 0;
}

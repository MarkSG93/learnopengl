#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

void render(GLFWwindow* window, unsigned int vao, unsigned int ebo, unsigned int textures[], Shader shader, glm::mat4 projection, glm::mat4 view, glm::vec3 cubePositions[]) {
  // Input
  processInput(window);

  // rendering commands
  glClearColor(0.2f, 0.8f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float time = (float)glfwGetTime();
//  model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//  trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

//  unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
//  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

//  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

  // Texture units
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[0]);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textures[1]);

  glBindVertexArray(vao);
  for(int i = 0; i < 10; i++) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;
    model = glm::rotate(model, time * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
//  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // indices haven't been defined yet in the tutorial

//  glBindVertexArray(0);

  // check and call events and swap the buffers
  glfwPollEvents();
  glfwSwapBuffers(window);
}

unsigned int generateTexture(const char* path, unsigned int colorChannelType) {
  stbi_set_flip_vertically_on_load(true);
  // binding texture object
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set texture wrapping options on the currently bound texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load texture
  int width, height, nrChannels;
  unsigned char *imageData = stbi_load(
    path,
    &width,
    &height,
    &nrChannels,
    0
  );

  // apply texture
  if (!imageData) {
    std::cout << "Failed to load texture" << std::endl;
    return -1;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, colorChannelType, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(imageData);
  return texture;
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
//  glViewport(0, 0, 1024, 768);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
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

  // Element Buffer Object
  unsigned int EBO;
  glGenBuffers(1, &EBO);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  int stride = 5 * sizeof(float);
  // Set the vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
  glEnableVertexAttribArray(0);

  //texture attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Shader shader("/Users/mark.griffiths/projects/open-gl/learnopengl/shaders/vertexshader.glsl", "/Users/mark.griffiths/projects/open-gl/learnopengl/shaders/fragmentshader.glsl");
  shader.loadShaders();

  unsigned int texture = generateTexture("/Users/mark.griffiths/projects/open-gl/learnopengl/textures/wood-planks.jpg", GL_RGB);
  unsigned int texture2 = generateTexture("/Users/mark.griffiths/projects/open-gl/learnopengl/textures/meme.png", GL_RGBA);

  unsigned int textures[] = { texture, texture2 };
  // Render loop
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  shader.use();
  shader.setInt("texture1", 0);
  shader.setInt("texture2", 1);

  glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)1024 / 768, 0.1f, 100.0f);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glEnable(GL_DEPTH_TEST);
  while(!glfwWindowShouldClose(window)) {
    render(window, VAO, EBO, textures, shader, projection, view, cubePositions);
  }

  glfwTerminate();
  return 0;
}

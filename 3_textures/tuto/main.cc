#include <iostream>
// GLEW

#include <SOIL.h>

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include <shader.hh>

int main()
{
  // Creating window
  sf::Window *window = new sf::Window(sf::VideoMode(800, 600), "OpenGL",
                                      sf::Style::Default, sf::ContextSettings(32));
  window->setVerticalSyncEnabled(true);
  if (glewInit() == GLEW_OK)
    std::cout << "Glew initialized successfully" << std::endl;
  // We create a VBO
  GLfloat vertices[] = {
      // Positions        // Color          // Texture Coords
      0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
      0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
      -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left
  };
  GLuint indices[] = {
      0, 1, 3,
      1, 2, 3
  };
  Shader shader("tuto/shaders/vertex_shader.glsl",
                "tuto/shaders/fragment_shader.glsl");
  int width, height;
  unsigned char *image = SOIL_load_image("../resources/textures/texture_test.png",
                                         &width, &height, 0, SOIL_LOAD_RGB);
  if (!image)
    std::cerr << "Cannot load image" << std::endl;
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
  int width2, height2;
  unsigned char *image2 = SOIL_load_image("../resources/textures/texture_test2.png",
                                          &width2, &height2, 0, SOIL_LOAD_RGB);
  if (!image2)
    std::cerr << "Cannot load image2" << std::endl;
  GLuint texture2;
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image2);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  GLuint EBO;
  glGenBuffers(1, &EBO);
  // VAO use
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  // Copy our vertices array in a buffer for OpenGL to use
  GLuint VBO; // Vertex Buffer Object
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
                        (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
                        (GLvoid*)(3 * sizeof (GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
                        (GLvoid*)(6 * sizeof (GLfloat)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);
  // We create a vertex shader
  bool running = true;
  while (running) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sf::Event event;
    while (window->pollEvent(event))
      if (event.type == sf::Event::Closed)
        running = false;
    shader.Use();
    glActiveTexture(GL_TEXTURE0); // activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, texture); // so we can bind it
    glUniform1i(glGetUniformLocation(shader.getProgram(), "uTexture"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "uTexture2"), 1);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    window->display();
  }
  delete window;
  return 0;
}

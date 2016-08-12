#include <iostream>
// GLEW
#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include "utils/shader_compiler.hh"

void print_info();

int main()
{
  // Creating window
  sf::Window *window = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
  window->setVerticalSyncEnabled(true);
  if (glewInit() == GLEW_OK)
    std::cout << "Glew initialized successfully" << std::endl;
  // We create a VBO
  GLfloat vertices[] = {
      0.5f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f
  };
  GLuint indices[] = {
      0, 1, 3,
      1, 2, 3
  };
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT),
                          (GLvoid*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  // We create a vertex shader
  GLuint vertexShader = shader_compiler::compile("hello_triangle_vertex.glsl", GL_VERTEX_SHADER);
  GLuint fragmentShader = shader_compiler::compile("hello_triangle_fragment_orange.glsl", GL_FRAGMENT_SHADER);
  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  GLint success;
  GLchar infolog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (success != GL_TRUE) {
    glGetShaderInfoLog(shaderProgram, 512, NULL, infolog);
    std::cout << "ERROR::PROGRAM::LINK::LINKING_FAILED\n"
    << infolog << std::endl;
    return 0;
  }
  bool running = true;
  while (running) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sf::Event event;
    while (window->pollEvent(event))
      if (event.type == sf::Event::Closed)
        running = false;
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    window->display();
  }
  delete window;
  return 0;
}

void print_info() {
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("GLSL version is (%s)\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

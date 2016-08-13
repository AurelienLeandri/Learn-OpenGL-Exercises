//
// Created by leo on 8/11/16.
//

#include <iostream>
// GLEW
#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include "../utils/shader_compiler.hh"

void print_info();

int main()
{
  sf::Window *window = new sf::Window(sf::VideoMode(800, 600), "Coucou",
    sf::Style::Default, sf::ContextSettings(32));
  window->setVerticalSyncEnabled(true);
  if (glewInit() == GLEW_OK)
    std::cout << "Glew initialized successfully" << std::endl;
  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      1.0f, 0.5f, 0.0f,
      1.5f, -0.5f, 0.0f
  };
  GLuint VAO1;
  glGenVertexArrays(1, &VAO1);
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindVertexArray(VAO1); {
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
      GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);
  }
  glBindVertexArray(0);
  GLuint VAO2;
  glGenVertexArrays(1, &VAO2);
  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindVertexArray(VAO2); {
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);
  }
  glBindVertexArray(0);
  GLuint vertexShader = shader_compiler::compile("hello_triangle_vertex.glsl",
    GL_VERTEX_SHADER);
  GLuint fragmentShader1 = shader_compiler::compile("hello_triangle_fragment_orange.glsl",
                                                 GL_FRAGMENT_SHADER);
  GLuint fragmentShader2 = shader_compiler::compile("hello_triangle_fragment_yellow.glsl",
                                                   GL_FRAGMENT_SHADER);
  GLuint shaderProgram1 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader1);
  glLinkProgram(shaderProgram1);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader1);
  GLint success;
  GLchar infolog[512];
  glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
  if (success != GL_TRUE) {
    glGetShaderInfoLog(shaderProgram1, 512, NULL, infolog);
    std::cout << "ERROR::PROGRAM::LINK::LINKING_FAILED\n"
    << infolog << std::endl;
    return 0;
  }
  GLuint shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader2);
  glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
  if (success != GL_TRUE) {
    glGetShaderInfoLog(shaderProgram2, 512, NULL, infolog);
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
    glUseProgram(shaderProgram1);
    glBindVertexArray(VAO1);
      glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO2);
      glDrawArrays(GL_TRIANGLES, 3, 3);
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

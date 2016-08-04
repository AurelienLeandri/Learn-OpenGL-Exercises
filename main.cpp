#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include "utils/file_reader.hh"


int main()
{
  // Creating window
  sf::Window *window = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
  window->setVerticalSyncEnabled(true);
  if (glewInit() == GLEW_OK)
    std::cout << "Glew initialized successfully" << std::endl;
  // We create a VBO
  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
  };
  GLuint VBO; // Vertex Buffer Object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // We create a vertex shader
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("GLSL version is (%s)\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  std::string str = file_reader::readFile("hello_triangle.glsl");
  const GLchar *vertexShaderSource = str.c_str();
  std::cout << vertexShaderSource << std::endl;
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  // Checking for compilation errors
  GLint success;
  GLchar infolog[512];
  int bufflen = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &bufflen);
  if (success != GL_TRUE) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
      << infolog << std::endl;
  }
  bool running = true;
  while (running) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sf::Event event;
    while (window->pollEvent(event))
      if (event.type == sf::Event::Closed)
        running = false;
    window->display();
  }
  delete window;
  return 0;
}

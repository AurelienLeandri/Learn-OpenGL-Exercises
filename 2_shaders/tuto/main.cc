#include <iostream>
// GLEW
#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include <shader.hh>

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
      0.0f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
  };
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
    glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  Shader shader("tuto/shaders/vertex_shader_ex3.glsl",
                "tuto/shaders/fragment_shader_ex3.glsl");
  // We create a vertex shader
  bool running = true;
  sf::Clock *clock = new sf::Clock();
  while (running) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sf::Event event;
    while (window->pollEvent(event))
      if (event.type == sf::Event::Closed)
        running = false;
    shader.Use();
    GLfloat  timeValue = clock->getElapsedTime().asSeconds();
    GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
    GLint vertexUniLocation = glGetUniformLocation(
        shader.getProgram(), "uni_color");
    GLint vHorizontalOffset = glGetUniformLocation(
        shader.getProgram(), "horizontalOffset");
    glUniform4f(vertexUniLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glUniform1f(vHorizontalOffset, 0.5f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    window->display();
  }
  delete clock;
  delete window;
  return 0;
}

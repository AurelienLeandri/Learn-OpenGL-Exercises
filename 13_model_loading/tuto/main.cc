#include <iostream>
// GLEW

#include <SOIL.h>

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include <shader.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hh"

void updateCamera(Camera &camera, float deltaTime, sf::Vector2f &formerPosition);

int main()
{
  // Creating window
  sf::Window *window = new sf::Window(sf::VideoMode(800, 600), "OpenGL",
                                      sf::Style::Default, sf::ContextSettings(32));
  window->setVerticalSyncEnabled(true);
  glEnable(GL_DEPTH_TEST);
  if (glewInit() == GLEW_OK)
    std::cout << "Glew initialized successfully" << std::endl;
  glm::mat4 model;
  glm::mat4 view;
  Camera camera;
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  Shader shader("tuto/shaders/vertex_shader.glsl",
                "tuto/shaders/fragment_shader.glsl");
  bool running = true;
  sf::Clock clock;
  sf::Vector2f mousePosition(sf::Mouse::getPosition());
  while (running) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sf::Event event;
    while (window->pollEvent(event))
      if (event.type == sf::Event::Closed)
        running = false;
    updateCamera(camera, clock.getElapsedTime().asSeconds(), mousePosition);
    shader.Use();
    GLint viewerLocPos = glGetUniformLocation(shader.getProgram(), "viewerPos");
    glUniform3f(viewerLocPos, camera.getPosition().x, camera.getPosition().y,
                camera.getPosition().z);
    window->display();
  }
  delete window;
  return 0;
}

// Camera controls
void updateCamera(Camera &camera, float deltaTime, sf::Vector2f &formerPosition) {
  sf::Vector2f newPosition(sf::Mouse::getPosition());
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
  camera.processMouse(newPosition.x - formerPosition.x,
                      formerPosition.y - newPosition.y);
  formerPosition = newPosition;
}

#include "model/model.hh"

#include <SOIL.h>

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hh"

void updateCamera(Camera &camera, float deltaTime, sf::Vector2f &formerPosition);

int main() {
  // Creating window
  sf::Window *window = new sf::Window(sf::VideoMode(800, 600), "OpenGL",
                                      sf::Style::Default, sf::ContextSettings(32));
  window->setVerticalSyncEnabled(true);
  glClearColor(0.07, 0.07, 0.07, 1);
  glEnable(GL_DEPTH_TEST);
  if (glewInit() == GLEW_OK)
    std::cout << "Glew initialized successfully" << std::endl;
  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
    clock.restart();
    window->display();
  }
  delete window;
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

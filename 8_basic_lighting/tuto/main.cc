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
  // We create a VBO
  GLfloat vertices[] = {
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,

      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,

      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,

      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,

      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,

      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
  };
  GLuint indices[] = {
      0, 1, 3,
      1, 2, 3,
      4, 5, 7,
      5, 6, 7,
      8, 9, 11,
      9, 10, 11,
      12, 13, 15,
      13, 14, 15,
      16, 17, 19,
      17, 18, 19,
      20, 21, 23,
      21, 22, 23
  };
  glm::mat4 model;
  glm::mat4 lightModel;
  glm::mat4 view;
  glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
  Camera camera;
// Note that we're translating the scene in the reverse direction of where we want to move
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  Shader shader("tuto/shaders/vertex_shader.glsl",
                "tuto/shaders/fragment_shader.glsl");
  Shader lightShader("tuto/shaders/light_vertex_shader.glsl",
                "tuto/shaders/light_fragment_shader.glsl");
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (GLvoid *) 0);
    glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  GLuint lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
    // We only need to bind to the VBO, the container's VBO's data already contains the correct data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
    // Set the vertex attributes (only position data for our lamp)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  // We create a vertex shader
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
    shader.Use();
    GLint objectColorLoc = glGetUniformLocation(shader.getProgram(), "objectColor");
    GLint lightColorLoc  = glGetUniformLocation(shader.getProgram(), "lightColor");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f); // Also set light's color (white)
    GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
    GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(VAO); {
      glm::mat4 model;
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
    lightShader.Use();
// Set the lightModel, view and projection matrix uniforms
    GLint lightModelLoc = glGetUniformLocation(lightShader.getProgram(), "model");
    glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
    GLint lightViewLoc = glGetUniformLocation(lightShader.getProgram(), "view");
    glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
    GLint lightProjLoc = glGetUniformLocation(lightShader.getProgram(), "projection");
    glUniformMatrix4fv(lightProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
// Draw the lamp object
    lightModel = glm::mat4();
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));
    glBindVertexArray(lightVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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

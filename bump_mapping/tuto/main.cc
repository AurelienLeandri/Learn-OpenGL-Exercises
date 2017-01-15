#include "model/model.hh"

#include <SOIL.h>

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hh"
#include <shader.hh>

void updateCamera(Camera &camera, float deltaTime, sf::Vector2f &formerPosition);
GLuint loadTexture(GLchar* path);

int main() {
  // Creating window
  sf::Window *window = new sf::Window(sf::VideoMode(800, 600), "OpenGL",
                                      sf::Style::Default, sf::ContextSettings(32));
  window->setVerticalSyncEnabled(true);
  glClearColor(0.07, 0.07, 0.07, 1);
  // Initialize GLEW to setup the OpenGL Function pointers
  if (glewInit() == GLEW_OK)
    std::cout << "Glew initialized successfully" << std::endl;
  // Define the viewport dimensions
  glViewport(0, 0, 800, 600);

  // Setup some OpenGL options
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Setup and compile our shaders
  GLuint program = glCreateProgram();
  std::string vertexCode = file_reader::readFile("tuto/shaders/advanced.vs.glsl");
  const GLchar *vShaderCode = vertexCode.c_str();
  GLuint vertex;
  Shader::compileShader(vertex, vShaderCode, GL_VERTEX_SHADER);
  glAttachShader(program, vertex);
  std::string geometryCode = file_reader::readFile("tuto/shaders/advanced.geo.glsl");
  const GLchar *gShaderCode = geometryCode.c_str();
  GLuint geometry;
  Shader::compileShader(geometry, gShaderCode, GL_GEOMETRY_SHADER);
  glAttachShader(program, geometry);
  std::string fragCode = file_reader::readFile("tuto/shaders/advanced.frag.glsl");
  const GLchar *fShaderCode = fragCode.c_str();
  GLuint frag;
  Shader::compileShader(frag, fShaderCode, GL_FRAGMENT_SHADER);
  glAttachShader(program, frag);
  glLinkProgram(program);

#pragma region "object_initialization"
  // Set the object data (buffers, vertex attributes)
  GLfloat planeVertices[] = {
      // Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
      1.0f,  -0.5f,  1.0f,  1.0f, 0.0f,
      -1.0f, -0.5f,  1.0f,  0.0f, 0.0f,
      -1.0f, -0.5f, -1.0f,  0.0f, 1.0f,
      1.0f,  -0.5f, -1.0f,  1.0f, 1.0f
  };
  GLuint indices[] = {
      0, 1, 2, 0, 2, 3
  };
  glm::vec3 light_pos(1.0, 1.0, 1.0);
  // Setup plane VAO
  GLuint planeVAO, planeVBO, planeEBO;
  glGenVertexArrays(1, &planeVAO);
  glGenBuffers(1, &planeVBO);
  glGenBuffers(1, &planeEBO);
  glBindVertexArray(planeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glBindVertexArray(0);

  GLuint floorTexture = loadTexture((GLchar*)"../resources/textures/brickwall.jpg");
#pragma endregion

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
  bool running = true;
  sf::Clock clock;
  sf::Vector2f mousePosition(sf::Mouse::getPosition());
  while (running) {
    sf::Event event;
    while (window->pollEvent(event))
      if (event.type == sf::Event::Closed)
        running = false;
    updateCamera(camera, clock.getElapsedTime().asSeconds(), mousePosition);
    clock.restart();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Set uniforms

    glUseProgram(program);
    GLint lightPosLoc = glGetUniformLocation(program, "lightPos");
    glUniform3f(lightPosLoc, light_pos.x, light_pos.y, light_pos.z);
    GLint viewPosLoc = glGetUniformLocation(program, "viewPos");
    glUniform3f(viewPosLoc, camera.getPosition().x,camera.getPosition().y, camera.getPosition().z);
    glUniform4f(glGetUniformLocation(program, "lightColor"), 1.0, 1.0, 1.0, 1.0);
    glm::mat4 model;
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(camera.getZoom(), (float)800/(float)600, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    // Floor
    glBindVertexArray(planeVAO);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    model = glm::mat4();
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    window->display();
  }
  delete window;
}

GLuint loadTexture(GLchar* path)
{
  //Generate texture ID and load texture data
  GLuint textureID;
  glGenTextures(1, &textureID);
  int width,height;
  unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
  // Assign texture to ID
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Parameters
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  SOIL_free_image_data(image);
  return textureID;
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

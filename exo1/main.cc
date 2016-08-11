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
  return 0;
}

void print_info() {
  printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
  printf("GLSL version is (%s)\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

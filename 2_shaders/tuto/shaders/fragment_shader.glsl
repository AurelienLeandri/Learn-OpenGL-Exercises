#version 450 core

in vec4 color_vertex;

out vec4 color_out;

void main() {
    color_out = color_vertex;
}

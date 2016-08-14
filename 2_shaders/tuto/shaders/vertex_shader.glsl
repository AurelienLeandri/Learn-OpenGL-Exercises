#version 450 core

layout (location = 0) in vec3 position;
out vec4 color_vertex;

void main() {
    gl_Position = vec4(position, 1.0);
    color_vertex = vec4(0.5f, 0.0f, 0.0f, 1.0f);
}

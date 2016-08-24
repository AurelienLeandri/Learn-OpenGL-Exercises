#version 450 core

uniform float horizontalOffset;

layout (location = 0) in vec3 position;
out vec4 color_vertex;

void main() {
    vec3 invertedPosition = vec3(position.x + horizontalOffset, -position.y, 0.0f);
    gl_Position = vec4(invertedPosition, 1.0);
    color_vertex = vec4(0.5f, 0.0f, 0.0f, 1.0f);
}

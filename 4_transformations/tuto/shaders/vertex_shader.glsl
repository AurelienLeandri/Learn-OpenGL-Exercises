#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
out vec3 vColor;
out vec2 vTexCoord;

uniform mat4 trans;

void main() {
    gl_Position = trans * vec4(position, 1.0f);
    vColor = color;
    vTexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}

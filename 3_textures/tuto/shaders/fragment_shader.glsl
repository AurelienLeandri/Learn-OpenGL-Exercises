#version 450 core

uniform sampler2D uTexture;

in vec3 vColor;
in vec2 vTexCoord;

out vec4 fColor;

void main() {
    fColor = texture(uTexture, vTexCoord);
}

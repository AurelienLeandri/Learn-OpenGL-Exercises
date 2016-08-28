#version 450 core

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

in vec3 vColor;
in vec2 vTexCoord;

out vec4 fColor;

void main() {
    fColor = mix(texture(uTexture, vTexCoord), texture(uTexture2, vTexCoord), 0.2);
}

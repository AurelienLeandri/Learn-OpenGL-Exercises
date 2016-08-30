#version 450 core

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

in vec2 vTexCoord;

vec2 vTexCoordFlip;

out vec4 fColor;

void main() {
    fColor = mix(texture(uTexture, vec2(vTexCoord.x, vTexCoord.y)),
        texture(uTexture2, vTexCoord), 0.2);
}

#version 450 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
    float ambient_strenght = 0.1f;
    vec3 light = lightColor * ambient_strenght;
    color = vec4(light * objectColor, 1.0f);
}

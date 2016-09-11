#version 450 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 fwd_normal;
in vec3 fragPos;

void main() {
    float ambient_strenght = 0.1f;
    vec3 ambientLight = lightColor * ambient_strenght;
    vec3 nNormal = normalize(fwd_normal);
    vec3 nFragPos = normalize(lightPos - fragPos);
    float diffLight = max(dot(nNormal, nFragPos), 0.0f);
    vec3 light = diffLight + ambientLight;
    color = vec4(light * objectColor, 1.0f);
}

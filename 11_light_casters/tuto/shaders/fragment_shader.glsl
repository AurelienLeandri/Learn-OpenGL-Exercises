#version 450 core

out vec4 color;

uniform vec3 viewerPos;

in vec3 fwd_normal;
in vec3 fragPos;
in vec2 TexCoords;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct Light {
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};

uniform Light light;

void main() {
    vec3 ambientLight = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 nNormal = normalize(fwd_normal);
    vec3 nFragPos = normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewerPos - fragPos);
    vec3 reflectDir = reflect(-nFragPos, nNormal);
    float specConst = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specLight = light.specular * (specConst * vec3(texture(material.specular, TexCoords)));
    float diffLight = max(dot(nNormal, nFragPos), 0.0f);
    vec3 diffuse = light.diffuse * (diffLight * vec3(texture(material.diffuse, TexCoords)));
    vec3 light = diffuse + ambientLight + specLight;
    color = vec4(light, 1.0f);
}

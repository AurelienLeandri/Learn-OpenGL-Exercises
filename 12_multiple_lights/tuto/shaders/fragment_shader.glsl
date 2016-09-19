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

float constant;
float linear;
float quadratic;

vec3 direction;
float cutOff;
float outerCutOff;
};

uniform Light light;

void main() {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +
        		    light.quadratic * (distance * distance));

    vec3 ambientLight = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 nNormal = normalize(fwd_normal);
    float diffLight = max(dot(nNormal, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * (diffLight * vec3(texture(material.diffuse, TexCoords)));

    vec3 viewDir = normalize(viewerPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, nNormal);
    float specConst = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specLight = light.specular * (specConst * vec3(texture(material.specular, TexCoords)));

    diffuse *= intensity;
    specLight *= intensity;
    ambientLight *= attenuation;
    diffuse *= attenuation;
    specLight *= attenuation;
    vec3 light = diffuse + ambientLight + specLight;
    color = vec4(light, 1.0f);
}

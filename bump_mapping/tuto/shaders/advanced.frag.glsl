#version 450

in vec3 normal;
in vec2 TexCoordsf;
in vec3 fragPosf;

out vec4 color;

uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform mat3 lightModel;
uniform vec3 viewPos;

void main()
{
    vec4 ambient_light_color = vec4(1.0, 1.0, 1.0, 1.0);
    float ambient_strenght = 0.1f;
    vec4 ambientLight = ambient_light_color * ambient_strenght;

    vec3 lightDir = normalize(lightPos - fragPosf);
    float diffuse_strength = max(dot(normal, lightDir), 0.0);
    vec4 diffuseLight = diffuse_strength * lightColor;

    float specularStrength = 1.0f;
    vec3 viewDir = normalize(viewPos - fragPosf);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specularLight = specularStrength * spec * lightColor;

    vec4 light = ambientLight + diffuseLight + specularLight;

    color = texture(texture1, TexCoordsf);
    color = light * color;
}
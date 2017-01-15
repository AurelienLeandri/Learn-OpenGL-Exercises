#version 450

layout (triangles) in;
in vec2[3] TexCoords;
in vec3[3] fragPos;

layout (triangle_strip, max_vertices = 3) out;
out vec2 TexCoordsf;
out vec3 fragPosf;
out vec3 normal;

vec3 getNormal()
{
   vec3 a = vec3(fragPos[0]) - vec3(fragPos[1]);
   vec3 b = vec3(fragPos[2]) - vec3(fragPos[1]);
   return normalize(cross(a, b));
}

void main() {
    normal = getNormal();
    for (int i = 0; i < gl_in.length(); i++) {
        gl_Position = gl_in[i].gl_Position;
        TexCoordsf = TexCoords[i];
        fragPosf = fragPos[i];
        EmitVertex();
    }
    EndPrimitive();
}

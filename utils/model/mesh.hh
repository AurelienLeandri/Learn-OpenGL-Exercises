//
// Created by leo on 9/25/16.
//

#ifndef OPENGL_TUTORIALS_MESH_HH
#define OPENGL_TUTORIALS_MESH_HH

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <shader.hh>
#include <assimp/types.h>

namespace model {
  struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  struct Texture {
    GLuint id;
    std::string type;
    aiString path;
  };

  class Mesh {
    public:
      Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
           std::vector<Texture> textures);
      void Draw(Shader shader);

    private:
      void setupMesh();
      std::vector<Vertex> vertices;
      std::vector<GLuint> indices;
      std::vector<Texture> textures;
      GLuint VAO;
      GLuint VBO;
      GLuint EBO;
  };

}


#endif //OPENGL_TUTORIALS_MESH_HH

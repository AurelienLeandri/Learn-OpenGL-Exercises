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

namespace model {
  struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  struct Texture {
    GLuint id;
    std::string type;
  };

  class Mesh {
    public:
    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    /*  Functions  */
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
         std::vector<Texture> textures);
    void Draw(Shader shader);
    private:
    /*  Render data  */
    GLuint VAO, VBO, EBO;
    /*  Functions    */
    void setupMesh();
  };

}


#endif //OPENGL_TUTORIALS_MESH_HH

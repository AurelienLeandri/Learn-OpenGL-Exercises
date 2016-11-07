//
// Created by leo on 9/25/16.
//

#ifndef OPENGL_TUTORIALS_MODEL_HH
#define OPENGL_TUTORIALS_MODEL_HH


#include <GL/glew.h>
#include <shader.hh>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.hh"

namespace model {

  class Model {
    public:
      Model(GLchar *path);
      void Draw(Shader shader);

    private:
      void loadModel(std::string path);
      void processNode(aiNode *node, const aiScene *scene);
      Mesh processMesh(aiMesh *mesh, const aiScene *scene);
      std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            std::string typeName);
      std::vector<Texture> textures_loaded;
      std::vector<Mesh> meshes;
      std::string directory;
  };

}


#endif //OPENGL_TUTORIALS_MODEL_HH

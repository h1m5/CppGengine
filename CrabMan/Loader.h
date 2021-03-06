//
//  Loader.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef Loader_h
#define Loader_h

#include <stdio.h>
#include <vector>
#include <GL/glew.h>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"

class Loader{
    
public:
    static Model* loadModel(std::string path, std::string textureFile = "");
    static Mesh* loadToVAO(std::vector<float> verts, int dimension);
    static int loadCubeMap(std::string textureFiles[]);
    static void bindIndices(std::vector<GLuint> indices);
    static void bindArrayBuffer(int attribNumber, int coordinates, std::vector<float> verts);
    static void unbindVAO();
    
private:
    static std::vector<GLuint> vaos;
    static GLuint createVAO();
    static Mesh* loadToVAO(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, bool hasMaterial, Material mat = Material{});
    static void storeDataInVAO(std::vector<Vertex> vertices, std::vector<GLuint> indices);
//    static GLuint TextureFromFile(const char* path, string directory);
    static void processNode(aiNode *node, const aiScene *scene, Model *model);
    static Mesh* processMesh(aiMesh* mesh, const aiScene* scene, Model *model);
    static vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, Model* model);
};

#endif /* Loader_h */

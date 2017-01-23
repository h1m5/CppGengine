//
//  Loader.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SOIL/SOIL.h>
#include "ResourceManager.h"
#include "Loader.h"

std::vector<GLuint> Loader::vaos;

Model* Loader::loadModel(string path, std::string textureFile, bool convertToUnitTransform)
{
    Model *model = new Model;
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path,
//                                           aiProcess_Triangulate |
                                           aiProcess_FlipUVs                |
                                           aiProcess_OptimizeMeshes         |
                                           aiProcess_CalcTangentSpace       |
                                           aiProcess_GenSmoothNormals       |
                                           aiProcess_SortByPType            |
                                           aiProcess_JoinIdenticalVertices |
                                           aiProcessPreset_TargetRealtime_MaxQuality);
    
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return nullptr;
    }
    model->setDirectory(path.substr(0, path.find_last_of('/')));
    
    aiMatrix4x4::Rotation(-45.0f, aiVector3D(1.0, 0.0, 0.0), scene->mRootNode->mTransformation);

    processNode(scene->mRootNode, scene, model);

    if(textureFile != ""){
//        if(!model->textures_loaded.empty()){
        model->textures_loaded.clear();
        //create new Texture
        Texture tex;
        tex.id = ResourseManager::getTexture(textureFile, "");
        tex.type = "";
        model->getMeshes()[0]->textures.push_back(tex);
        model->getMeshes()[0]->setHasMaterial(false);
        //            model->textures_loaded.push_back(tex);
        //        }
    }
    
    if (convertToUnitTransform)
        model->transformToUnitCoordinates(scene->mRootNode);
    
    return model;
}

void Loader::processNode(aiNode *node, const aiScene *scene, Model *model)
{
    node->mTransformation = scene->mRootNode->mTransformation * node->mTransformation;
    
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        model->addMesh(processMesh(mesh, scene, model));
    }
    
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, model);
    }
}

int totalIndices = 0;
Mesh* Loader::processMesh(aiMesh* mesh, const aiScene* scene, Model* model)
{
    // Data to fill
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    
    unsigned indexOffset = totalIndices;
    unsigned int indexCountBefore = totalIndices;
    
    // Walk through each of the mesh's vertices
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // Positions
        vector.x = mesh->mVertices[i].x; model->m_vertices.push_back(vector.x);
        vector.y = mesh->mVertices[i].y; model->m_vertices.push_back(vector.y);
        vector.z = mesh->mVertices[i].z; model->m_vertices.push_back(vector.z);
        vertex.position = vector;
        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        // Texture Coordinates
        if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for(GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
            model->m_indices.push_back(face.mIndices[j]);
        }
    }
    // Process materials
    Material mmat;
    bool hasMaterial = false;
    bool hasTexture = false;
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // Diffuse: texture_diffuseN
        // Specular: texture_specularN
        // Normal: texture_normalN
        
        // 1. Diffuse maps
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", model);
        if(diffuseMaps.size() != 0) hasTexture = true;
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. Specular maps
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", model);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        
        aiColor4D diffuse;
        if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse)){
            hasMaterial = true;
            mmat.diffuse = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
        }
        
        aiColor4D specular;
        if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular))
            mmat.specular = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
    }
    
    // Return a mesh object created from the extracted mesh data
    if(hasTexture) hasMaterial = false;
    
    auto aMesh = loadToVAO(vertices, indices, textures, hasMaterial, mmat);
    aMesh->indexCount = indices.size() - indexCountBefore;
    return aMesh;
}

vector<Texture> Loader::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, Model* model)
{
    vector<Texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        GLboolean skip = false;
        for(GLuint j = 0; j < model->textures_loaded.size(); j++)
        {
            if(model->textures_loaded[j].path == str)
            {
                textures.push_back(model->textures_loaded[j]);
                skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // If texture hasn't been loaded already, load it
            Texture texture;
//            texture.id = TextureFromFile(str.C_Str(), model->getDirectory());
            texture.id = ResourseManager::getTexture(str.C_Str(), model->getDirectory());
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            model->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

Mesh* Loader::loadToVAO(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, bool hasMaterial, Material mmat)
{
    GLuint vaoID = createVAO();
    storeDataInVAO(vertices, indices);
    return new Mesh(vaoID, (int)indices.size(), textures, hasMaterial, mmat);
}

GLuint Loader::createVAO()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    vaos.push_back(vaoID);
    return vaoID;
}

Mesh* Loader::loadToVAO(std::vector<float> verts, int dimension)
{
    int vaoID = createVAO();
    bindArrayBuffer(0, dimension, verts);
    unbindVAO();
    return new Mesh(vaoID, verts.size());
}

int Loader::loadCubeMap(std::string textureFiles[])
{
    GLuint texId;
    glGenTextures(1, &texId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
    
    for(int i=0; i<6; i++){
        int w, h;
        std::cout << textureFiles[i] << std::endl;
        unsigned char *img = SOIL_load_image(textureFiles[i].c_str(), &w, &h, 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    return texId;
}

void Loader::storeDataInVAO(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    bindIndices(indices);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
    
    std::cout <<"count: " <<vertices.size() << std::endl;
    glBindVertexArray(0);
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}

void Loader::bindArrayBuffer(int attribNumber, int coordinates, std::vector<float> verts)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(attribNumber);
    glVertexAttribPointer(attribNumber, coordinates, GL_FLOAT, GL_FALSE, sizeof(float), 0);
}

void Loader::bindIndices(std::vector<GLuint> indices)
{
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

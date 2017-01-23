//
//  Mesh.h
//  nfghdg
//
//  Created by Imhoisili Otokhagua on 27/01/15.
//  Copyright (c) 2015 TriKomand. All rights reserved.
//

#ifndef __nfghdg__Mesh__
#define __nfghdg__Mesh__

#include <iostream>
#include "maths.h"
#include <vector>
#include <GL/glew.h>
#include <assimp/types.h>

using namespace std;

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture{
    GLuint id;
    string type;
    aiString path;
};

struct Material{
    glm::vec4 diffuse;
    glm::vec4 specular;
};

class Mesh {
    GLuint VAO;
    Material _material;
    bool _hasMaterial;
    
public:
    
    Mesh(GLuint vao, int indexOffset, std::vector<Texture> textures = std::vector<Texture>(), bool hasMaterial = false, Material mat = Material{})
    {
        VAO = vao;
        this->indexOffset = indexOffset;
        this->textures = textures;
        this->_material = mat;
        this->_hasMaterial = hasMaterial;
    }
    
    int indexOffset;
    int indexCount;
    void setHasMaterial(bool has) { _hasMaterial = has; }
    
    std::vector<Texture> textures;
    GLuint getVaoID() {return VAO;}
    Material getMaterial() { return _material; }
    bool getHasMaterial() { return _hasMaterial; }
    int getVertexCount() {return indexOffset;}
};

#endif /* defined(__nfghdg__Mesh__) */

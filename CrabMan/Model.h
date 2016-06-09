//
//  Model.h
//  nfghdg
//
//  Created by Imhoisili Otokhagua on 27/01/15.
//  Copyright (c) 2015 TriKomand. All rights reserved.
//

#ifndef __nfghdg__Model__
#define __nfghdg__Model__

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model {
    vector<Mesh*> meshes;
    string directory;
    
public:
//    Model(string path){}
    std::string getDirectory(){return directory;}
    void setDirectory(std::string dir){directory = dir;}
    vector<Texture> textures_loaded;
    Model(){}
    void addMesh(Mesh* m){meshes.push_back(m);}
    vector<Mesh*> getMeshes() { return meshes; }
    
//    void Draw(Shader shader);
};

#endif /* defined(__nfghdg__Model__) */

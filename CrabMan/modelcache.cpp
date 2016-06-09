//
//  modelcache.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "modelcache.h"
#include "Loader.h"

ModelCache::ModelCache()
{
    
}

ModelCache::~ModelCache()
{
    
}

Model* ModelCache::getModel(std::string name, std::string textureName)
{
    
    if(textureName != "")
        textureName = textureName;
    
    auto mit = _modelMap.find(name);
    
    if(mit == _modelMap.end())//if relative path fails
    {
        //use absolute path
        Model* model = Loader::loadModel(name, textureName);
        _modelMap.insert(make_pair(name, model));
        return model;
    }
    
    return mit->second;
}

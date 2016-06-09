//
//  modelcache.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef modelcache_h
#define modelcache_h

#include "model.h"
#include <map>

class ModelCache {
public:
    ModelCache();
    ~ModelCache();
    
    Model* getModel(std::string name, std::string textureName, std::string dir);
    
private:
    std::map<std::string, Model*> _modelMap;
};

#endif /* modelcache_h */

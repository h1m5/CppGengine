//
//  shadercache.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef shadercache_h
#define shadercache_h

#include <stdio.h>
#include <map>
#include "staticshader.h"

class ShaderCache{
public:
    
    StaticShader* getStaticShaderProgram(std::string name);
    
private:
    std::map<std::string, StaticShader*> staticShaderCache;
};

#endif /* shadercache_h */

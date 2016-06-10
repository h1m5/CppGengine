//
//  shadercache.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "shadercache.h"

StaticShader* ShaderCache::getStaticShaderProgram(std::string name)
{
    std::string vert = name + ".vert";
    std::string frag = name + ".frag";
    
    std::cout << "is here" << std::endl;
    auto sit = staticShaderCache.find(name);
    if(sit == staticShaderCache.end())
    {
        std::cout << "init_vert: "<< vert << std::endl;
        std::cout << "init_frag: "<< frag << std::endl;
        
        StaticShader *program = new StaticShader(vert, frag);
//        StaticShader *program = new StaticShader(name + ".vert", name + ".frag");
        staticShaderCache.insert(make_pair(name, program));
        return program;
    }
    
    return sit->second;
}
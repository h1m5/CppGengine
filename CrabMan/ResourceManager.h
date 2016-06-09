//
//  ResourceManager.hpp
//  GraphicsTutorial
//
//  Created by Imhoisili Otokhagua on 20/07/15.
//  Copyright © 2015 TriKomand. All rights reserved.
//

#ifndef ResourceManager_h
#define ResourceManager_h

#include <stdio.h>
#include "TextureCache.h"
#include "shadercache.h"
#include "modelcache.h"
#include "viewStateCache.h"
#include <string>


class ResourseManager
{
public:
    static GLuint getTexture(std::string texturePath, std::string directory);
    static StaticShader* getStaticShader(std::string name, std::string dir = workingDirectory);
    static Model* getModel(std::string name, std::string textureName, std::string dir = workingDirectory);
    static ViewingState* getViewState(ViewMode mode);
    static std::string workingDirectory;
    
private:
    static TextureCache _textureCache;
    static ShaderCache _shaderCache;
    static ModelCache _modelCache;
    static ViewingStateCache _viewStatCache;
};

#endif /* ResourceManager_cpp */

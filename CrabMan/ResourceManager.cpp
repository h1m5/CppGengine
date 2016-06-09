//
//  ResourceManager.cpp
//  GraphicsTutorial
//
//  Created by Imhoisili Otokhagua on 20/07/15.
//  Copyright © 2015 TriKomand. All rights reserved.
//

#include "ResourceManager.h"

TextureCache ResourseManager::_textureCache;
ShaderCache ResourseManager::_shaderCache;
ModelCache ResourseManager::_modelCache;
ViewingStateCache ResourseManager::_viewStatCache;

GLuint ResourseManager::getTexture(std::string texturePath, std::string directory)
{
    return  _textureCache.getTexture(texturePath, directory);
}

StaticShader* ResourseManager::getStaticShader(std::string name)
{
    return _shaderCache.getStaticShaderProgram(name);
}

Model* ResourseManager::getModel(std::string name, std::string textureName)
{
    return _modelCache.getModel(name, textureName);
}

ViewingState* ResourseManager::getViewState(ViewMode mode)
{
    return _viewStatCache.getViewMode(mode);
}
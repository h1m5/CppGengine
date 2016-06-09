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
std::string ResourseManager::workingDirectory;

GLuint ResourseManager::getTexture(std::string texturePath, std::string directory)
{
    return  _textureCache.getTexture(texturePath, directory);
}

StaticShader* ResourseManager::getStaticShader(std::string name, std::string dir)
{
    return _shaderCache.getStaticShaderProgram(name, dir);
}

Model* ResourseManager::getModel(std::string name, std::string textureName, std::string dir)
{
    return _modelCache.getModel(name, textureName, dir);
}

ViewingState* ResourseManager::getViewState(ViewMode mode)
{
    return _viewStatCache.getViewMode(mode);
}
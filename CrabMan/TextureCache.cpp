//
//  TextureCache.cpp
//  GraphicsTutorial
//
//  Created by Imhoisili Otokhagua on 20/07/15.
//  Copyright © 2015 TriKomand. All rights reserved.
//

#include "TextureCache.h"
#include <SDL2/SDL_image.h>
#include <SOIL/SOIL.h>
#include <iostream>


TextureCache::TextureCache()
{
    
}

TextureCache::~TextureCache()
{
    
}

GLuint TextureCache::getTexture(std::string texturePath, std::string directory)
{
    //lookup the texture and see if it's in the map
    //    std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
    //same as
    auto mit = _textureMap.find(texturePath);
    
    if(mit == _textureMap.end()){
        GLuint newTextureId = TextureFromFile(texturePath, directory);
        
        _textureMap.insert(make_pair(texturePath, newTextureId));
        //            _textureMap[texturePath] = newTexture;
        return newTextureId;
    }
    return mit->second;
}

GLuint TextureCache::TextureFromFile(std::string path, std::string directory)
{
    //Generate texture ID and load texture data
    std::string filename = path;
    filename = directory == "" ? filename : directory + '/' + filename;
//    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int w, h;
    unsigned char *img = SOIL_load_image(filename.c_str(), &w, &h, 0, SOIL_LOAD_RGBA);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_MAX_TEXTURE_LOD_BIAS, 0);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SOIL_free_image_data(img);
    return textureID;
}
//
//  TextureCache.hpp
//  GraphicsTutorial
//
//  Created by Imhoisili Otokhagua on 20/07/15.
//  Copyright © 2015 TriKomand. All rights reserved.
//

#ifndef TextureCache_cpp
#define TextureCache_cpp

#include <stdio.h>
#include <string>
#include <GL/glew.h>
#include <map>

class TextureCache {
public:
    TextureCache();
    ~TextureCache();
    
    GLuint getTexture(std::string texturePath, std::string directory);
    
private:
    GLuint TextureFromFile(std::string path, std::string directory);
    std::map<std::string, GLuint> _textureMap;
};
#endif /* TextureCache_cpp */

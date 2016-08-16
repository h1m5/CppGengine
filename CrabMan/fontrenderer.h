//
//  fontrenderer.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 15/08/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef fontrenderer_h
#define fontrenderer_h

#include <stdio.h>
#include <ft2build.h>
#include "maths.h"
#include "fontShader.h"
#include <map>
#include <string>
#include FT_FREETYPE_H

struct Character {
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
};

class FontRenderer {
public:
    void init(std::string shaderName, std::string fontName);
    static FontRenderer* sharedInstance();
    void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    
private:
    FontRenderer() {}
    FontRenderer(const FontRenderer &) = delete;
    
    void createProjectionMatrix();
    void enableBlending();
    void configureTextureQuad();
    
    void loadFont(const char* fontFile);
    std::map<GLchar, Character> characters;
    FontShader *_shader;
    glm::mat4 pMatrix;
    
    GLuint VAO;
    GLuint VBO;
};

#endif /* fontrenderer_h */

//
//  fontShader.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 16/08/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef fontShader_h
#define fontShader_h

#include "shaderprogram.h"


class FontShader : public ShaderProgram{
public:
    
    FontShader(std::string vertexFile, std::string fragmentFile);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadTextColor(float r, float g, float b);
    
    void getAllUniforms();
    void bindAttributes();
    
private:
    GLuint pMatrix;
    GLuint textColor;
};

#endif /* fontShader_h */

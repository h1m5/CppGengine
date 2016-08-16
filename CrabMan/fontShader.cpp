//
//  fontShader.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 16/08/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "fontShader.h"

FontShader::FontShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
    getAllUniforms();
    bindAttributes();
}

void FontShader::loadProjectionMatrix(glm::mat4 matrix)
{
    loadMatrix(pMatrix, matrix);
}

void FontShader::loadTextColor(float r, float g, float b)
{
    loadVector(textColor, glm::vec3(r,g,b));
}

void FontShader::getAllUniforms()
{
    pMatrix = getUniformLocation("pMatrix");
    textColor = getUniformLocation("textColor");
}

void FontShader::bindAttributes()
{
    bindAttribute(0, "vertex");
}
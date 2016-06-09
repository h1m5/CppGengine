//
//  shaderprogram.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef shaderprogram_h
#define shaderprogram_h

#include <GL/glew.h>
#include <string>
#include "maths.h"

class ShaderProgram{
public:
    ShaderProgram(std::string vertexFile, std::string fragmentFile);
    void start();
    void stop();
    
protected:
    void bindAttribute(GLuint location, std::string attribute);
    virtual void getAllUniforms()=0;
    virtual void bindAttributes()=0;
    GLuint getUniformLocation(std::string value);
    void loadInt(GLuint location, int value);
    void loadBool(GLuint location, bool value);
    void loadFloat(GLuint location, GLfloat value);
    void loadVector(GLuint location, glm::vec3 value);
    void load4DVector(GLuint location, glm::vec4 value);
    void load2DVector(GLuint location, glm::vec2 value);
    void loadMatrix(GLuint location, glm::mat4 matrix);
    
private:
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;
    std::string name;
    
    GLuint loadShader(std::string file, int type);
    void loadProgram();
    void checkCompileErrors(GLuint object, int type);
};

#endif /* shaderprogram_h */

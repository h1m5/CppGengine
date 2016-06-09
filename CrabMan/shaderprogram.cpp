//
//  shaderprogram.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include <iostream>
#include "shaderprogram.h"
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile)
{
    vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    loadProgram();
//    getAllUniforms();
}

void ShaderProgram::bindAttribute(GLuint location, std::string attribute)
{
    glBindAttribLocation(programID, location, attribute.c_str());
}

void ShaderProgram::start()
{
    glUseProgram(programID);
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}

GLuint ShaderProgram::getUniformLocation(std::string value)
{
    return glGetUniformLocation(programID, value.c_str());
}

void ShaderProgram::loadInt(GLuint location, int value)
{
    glUniform1i(location, value);
}

void ShaderProgram::loadFloat(GLuint location, GLfloat value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(GLuint location, glm::vec3 value)
{
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::load4DVector(GLuint location, glm::vec4 value)
{
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::load2DVector(GLuint location, glm::vec2 value)
{
    glUniform2f(location, value.x, value.y);
}

void ShaderProgram::loadMatrix(GLuint location, glm::mat4 matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::loadBool(GLuint location, bool value)
{
    glUniform1f(location, value);
}

GLuint ShaderProgram::loadShader(std::string file, int type)
{
    std::string shaderSource;
    try {
        std::ifstream shaderFile(file);
        std::stringstream stream;
        
        stream << shaderFile.rdbuf();
        shaderFile.close();
        shaderSource = stream.str();
        
    } catch (std::exception e) {
        std::cout << "\nError::Shader: Failed to read shader" << e.what() << std::endl;
    }
    
    const GLchar *shaderCode = shaderSource.c_str();
    
    GLuint shaderHandle;
    
    shaderHandle = glCreateShader(type);
    glShaderSource(shaderHandle, 1, &shaderCode, NULL);
    glCompileShader(shaderHandle);
    checkCompileErrors(shaderHandle, type);
    return shaderHandle;
}

void ShaderProgram::loadProgram()
{
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
//    bindAttributes();
//    bindAttribute(0, "vert");
//    bindAttribute(1, "normal");
//    bindAttribute(2, "tCoord");
    glLinkProgram(programID);
    glValidateProgram(programID);
    checkCompileErrors(programID, 3);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void ShaderProgram::checkCompileErrors(GLuint object, int type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != 3)
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
            << infoLog << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
            << infoLog << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
    }
}

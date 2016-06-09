//
//  staticshader.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef staticshader_h
#define staticshader_h

#include <stdio.h>
#include "shaderprogram.h"
#include "light.h"
#include "camera3D.h"
#define MAX_LIGHTS 5
#include <vector>

class StaticShader : public ShaderProgram{
public:
    StaticShader(std::string vertexFile, std::string fragmentFile);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(Camera *camera);
    void loadModelMatrix(glm::mat4 matrix);
    void loadLight(std::vector<Light*> &lights);
    void loadTextureUnits();
    void loadDiffuseTextureUnit(GLuint un);
    void loadSpecularTextureUnit(GLuint un);
    void loadSkyColour(float r, float g, float b);
    void loadMaterial(bool hasMaterial, glm::vec4 diffuse = glm::vec4(0.1,0.1,0.1,1.0), glm::vec4 specular = glm::vec4(0.1,0.1,0.1,1.0));
    
protected:
    virtual void getAllUniforms();
    virtual void bindAttributes();
private:
    
    GLuint pMatrix;
    GLuint vMatrix;
    GLuint mMatrix;
    GLuint cameraPosition;
    GLuint shininess;
    GLuint diffuseTexUnit;
    GLuint specularTexUnit;
    GLuint materialDiffuse;
    GLuint materialSpecular;
    GLuint hasMaterial;
    GLuint skyColour;
    
    GLuint lightColor[MAX_LIGHTS];
    GLuint lightPosition[MAX_LIGHTS];
    GLuint attenuation[MAX_LIGHTS];
};

#endif /* staticshader_h */
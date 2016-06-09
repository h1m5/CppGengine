//
//  staticshader.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "staticshader.h"

StaticShader::StaticShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
    getAllUniforms();
}

void StaticShader::getAllUniforms()
{
    pMatrix = getUniformLocation("pMatrix");
    vMatrix = getUniformLocation("vMatrix");
    mMatrix = getUniformLocation("mMatrix");
    cameraPosition = getUniformLocation("cameraPosition");
    shininess = getUniformLocation("shininess");
    diffuseTexUnit = getUniformLocation("texDiffuse");
    specularTexUnit = getUniformLocation("texSpecular");
    materialSpecular = getUniformLocation("material.specular");
    materialDiffuse = getUniformLocation("material.diffuse");
    hasMaterial = getUniformLocation("hasMaterial");
    skyColour = getUniformLocation("skyColour");
    
    for(int i=0; i<MAX_LIGHTS; i++){
        lightPosition[i] = getUniformLocation("lightPosition[" + std::to_string(i) + "]");
        lightColor[i] = getUniformLocation("lightColor[" + std::to_string(i) + "]");
        attenuation[i] = getUniformLocation("attenuation[" + std::to_string(i) + "]");
    }
}

void StaticShader::bindAttributes()
{
    bindAttribute(0, "vert");
    bindAttribute(1, "normal");
    bindAttribute(2, "tCoord");
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
    loadMatrix(pMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera *camera)
{
    loadMatrix(vMatrix, camera->createViewMatrix());
    loadVector(cameraPosition, camera->getPosition());
}

void StaticShader::loadModelMatrix(glm::mat4 matrix)
{
    loadMatrix(mMatrix, matrix);
}

void StaticShader::loadLight(std::vector<Light*> &lights)
{
    loadFloat(shininess, 10.0f);
    for(int i=0; i<MAX_LIGHTS; i++){
        if(i < lights.size()){
            loadVector (attenuation[i], lights[i]->getAttenuation());
            loadVector(lightPosition[i], lights[i]->getPosition());
            loadVector(lightColor[i], lights[i]->getColor());
        } else {
            loadVector (attenuation[i], glm::vec3(1, 0, 0));
            loadVector(lightPosition[i], glm::vec3(0, 0, 0));
            loadVector(lightColor[i], glm::vec3(0, 0, 0));
        }
    }
}

void StaticShader::loadSkyColour(float r, float g, float b)
{
    loadVector(skyColour, glm::vec3(r,g,b));
}

void StaticShader::loadDiffuseTextureUnit(GLuint un)
{
    loadFloat(diffuseTexUnit, un);
}

void StaticShader::loadSpecularTextureUnit(GLuint un)
{
    loadFloat(specularTexUnit, un);
}

void StaticShader::loadMaterial(bool hasMaterial, glm::vec4 diffuse, glm::vec4 specular)
{
    load4DVector(materialDiffuse, diffuse);
    load4DVector(materialSpecular, specular);
    loadBool(StaticShader::hasMaterial, hasMaterial);
}

void StaticShader::loadTextureUnits()
{
    loadInt(diffuseTexUnit, 0);
    loadInt(specularTexUnit, 1);
}


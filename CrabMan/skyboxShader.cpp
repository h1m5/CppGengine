//
//  skyboxShader.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 03/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "skyboxShader.h"
#include "ResourceManager.h"
#include "maths.h"

//std::string SkyboxShader::VERTEX_FILE = "/skybox.vert";
//std::string SkyboxShader::FRAGMENT_FILE = ResourseManager::workingDirectory + "/skybox.frag";
std::string SkyboxShader::VERTEX_FILE = "res/skybox.vert";
std::string SkyboxShader::FRAGMENT_FILE = "res/skybox.frag";

SkyboxShader::SkyboxShader()  : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
    getAllUniforms();
}

void SkyboxShader::getAllUniforms()
{
    location_projectionMatrix = getUniformLocation("pMatrix");
    location_viewMatrix = getUniformLocation("vMatrix");
    location_modelMatrix = getUniformLocation("mMatrix");
    location_fogColour = getUniformLocation("fogColour");
    location_blendFactor = getUniformLocation("blendFactor");
    location_cubeMap = getUniformLocation("cubeMap");
    location_cubeMap2 = getUniformLocation("cubeMap2");
}

void SkyboxShader::bindAttributes()
{
    bindAttribute(0, "position");
}

void SkyboxShader::connectTextureUnits()
{
    loadInt(location_cubeMap, 0);
    loadInt(location_cubeMap2, 1);
}

void SkyboxShader::loadBlendFactor(float blendFactor)
{
    loadFloat(location_blendFactor, blendFactor);
}

void SkyboxShader::loadFogColour(float r, float g, float b)
{
    loadVector(location_fogColour, glm::vec3(r, g, b));
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 mat)
{
    loadMatrix(location_projectionMatrix, mat);
}

void SkyboxShader::loadModelMatrix(glm::mat4 mat)
{
    loadMatrix(location_modelMatrix, mat);
}

void SkyboxShader::loadViewMatrix(Camera *camera)
{
    
//    QMatrix4x4 view = cam->getViewMatrix ();
//    view.setColumn (3, QVector4D(1, 1, 1, 1));
//    view.setRow (3, QVector4D(0, 0, 0, 1));
    
    glm::mat4 vMatrix = camera->createViewMatrix();
    vMatrix[3].x = 1; vMatrix[3].y = 1; vMatrix[3].z = 1; vMatrix[3].w = 1;
    vMatrix[0].w = 0; vMatrix[1].w = 0; vMatrix[2].w = 0; vMatrix[3].w = 1;
    loadMatrix(location_viewMatrix, vMatrix);
}
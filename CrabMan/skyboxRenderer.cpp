//
//  skyboxRenderer.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 03/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "ResourceManager.h"
#include "skyboxRenderer.h"

float SkyboxRenderer::SIZE = 500.0f;
std::string SkyboxRenderer::TEXTURE_FILES[] = {
    "right.png", "left.png", "top.png", "bottom.png", "back.png", "front.png"
};

SkyboxRenderer::SkyboxRenderer(glm::mat4 projectionMatrix, float r, float g, float b)
{
    _cube = new Entity(ResourseManager::getModel("res/cube.obj",""), glm::vec3(0,0,0),0,0,0, SIZE);
    
    _texture = Loader::loadCubeMap(TEXTURE_FILES);
    _shader = new SkyboxShader();
    _shader->start();
    _shader->connectTextureUnits();
    _shader->loadFogColour(r, g, b);
    _shader->loadProjectionMatrix(projectionMatrix);
    _shader->stop();
}

void SkyboxRenderer::bindTextures()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    _shader->loadBlendFactor(0.2);
}

void SkyboxRenderer::render(Camera *camera)
{
    _shader->start();
    _shader->loadViewMatrix(camera);
    glm::mat4 mMatrix = Maths::createTransformationMatrix(_cube->getPosition(),
                                                          _cube->getRotX(),
                                                          _cube->getRotY(),
                                                          _cube->getRotZ(),
                                                          _cube->getScale());
    
    _shader->loadModelMatrix(mMatrix);
    bindTextures();
    
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    for(Mesh* m : _cube->getModel()->getMeshes()){
        glBindVertexArray(m->getVaoID());
        glDisable(GL_CULL_FACE);
        glDrawElements(GL_TRIANGLES,m->getVertexCount(), GL_UNSIGNED_INT, 0);
        glEnable(GL_CULL_FACE);
    }
    glDepthMask(GL_TRUE);
    
    glBindVertexArray(0);
    _shader->stop();
    
}

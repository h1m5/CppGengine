//
//  entityrenderer.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "entityrenderer.h"
#include "ResourceManager.h"
#include "maths.h"
#include "DisplayManager.h"
#define RED 0.8
#define GREEN 0.8
#define BLUE 0.9

float EntityRenderer::FOV = 60.0f;

EntityRenderer::EntityRenderer(StaticShader *shader)
{
    _shader = shader;
}

EntityRenderer::EntityRenderer(std::string shaderName)
{
    _shader = ResourseManager::getStaticShader(shaderName);
    createProjectionMatrix();
    _shader->start();
    _shader->loadProjectionMatrix(pMatrix);
    _shader->stop();
    enableCulling();
}

void EntityRenderer::prepareMesh(Mesh *mesh)
{
    for(GLuint i=0; i<mesh->textures.size(); i++)
    {
        //            std::cout << m->textures[i].path.C_Str() << m->textures[i].id << std::endl;
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
    }
}

void EntityRenderer::unbindTextures(Mesh *mesh)
{
        for(GLuint i=0; i<mesh->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 +i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
}

void EntityRenderer::render(Entity *entity, Camera* camera, std::vector<Light*> &lights)
{
    prepare();
    _shader->start();
    
    glm::mat4 mMatrix = Maths::createTransformationMatrix(entity->getPosition(),
                                                          entity->getRotX(),
                                                          entity->getRotY(),
                                                          entity->getRotZ(),
                                                          entity->getScale());
    
    _shader->loadSkyColour(RED, GREEN, BLUE);
    _shader->loadModelMatrix(mMatrix);
    _shader->loadViewMatrix(camera);
    _shader->loadLight(lights);
    
    Model *model = entity->getModel();
    for(Mesh* m : model->getMeshes()){
        glBindVertexArray(m->getVaoID());
        prepareMesh(m);
        _shader->loadMaterial(m->getHasMaterial(), m->getMaterial().diffuse, m->getMaterial().specular);
        glDrawElements(GL_TRIANGLES, m->getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindTextures(m);
        glBindVertexArray(0);
    }
    _shader->stop();
}

void EntityRenderer::prepare()
{
    glClearColor(RED, GREEN, BLUE, 1.0f);
    
    //Enable multisampling
    glEnable(GL_MULTISAMPLE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void EntityRenderer::createProjectionMatrix()
{
    pMatrix = glm::mat4();
    pMatrix = glm::perspective(FOV, (GLfloat)Window::getWidth()/Window::getHeight(), 0.1f, 1000.0f);
}

void EntityRenderer::enableCulling()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
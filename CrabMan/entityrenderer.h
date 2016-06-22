//
//  entityrenderer.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef entityrenderer_h
#define entityrenderer_h

#include <stdio.h>
#include "staticshader.h"
#include "Model.h"
#include "camera3D.h"
#include "entity.h"

class EntityRenderer : public Subscriber {
public:
    EntityRenderer(StaticShader *shader);
    EntityRenderer(std::string shaderName);
    
    
//    void render(Model* model, Camera* camera, std::vector<Light*> &lights);
    void render(Entity *model, Camera* camera, std::vector<Light*> &lights);
    void prepareMesh(Mesh* model);
    void prepare();
    void createProjectionMatrix();
    void unbindTextures(Mesh* mesh);
    void update(SDL_Event *ev);
    glm::mat4 getProjectionMatrix() { return pMatrix; }
    
private:
    void enableCulling();
    StaticShader *_shader;
    glm::mat4 pMatrix;
    static float FOV;
};

#endif /* entityrenderer_h */

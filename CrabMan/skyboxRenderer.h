//
//  skyboxRenderer.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 03/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef skyboxRenderer_h
#define skyboxRenderer_h

#include <stdio.h>
#include "Mesh.h"
#include "Loader.h"
#include "maths.h"
#include "skyboxShader.h"

class SkyboxRenderer {
public:
    SkyboxRenderer(glm::mat4 projectionMatrix, float r = 0.8f, float g = 0.8f, float b = 0.9f);
    void render(Camera *camera);
    void bindTextures();
    
private:
    static float SIZE;
    static std::string TEXTURE_FILES[];
    
    GLuint _texture;
    Entity *_cube;
    
    SkyboxShader *_shader;
};

#endif /* skyboxRenderer_h */

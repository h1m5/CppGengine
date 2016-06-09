//
//  skyboxShader.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 03/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef skyboxShader_h
#define skyboxShader_h

#include "shaderprogram.h"
#include <iostream>
#include <string>
#include "camera.h"

class SkyboxShader : public ShaderProgram {
public:
    SkyboxShader();
    void connectTextureUnits();
    void loadProjectionMatrix(glm::mat4 mat);
    void loadModelMatrix(glm::mat4 mat);
    void loadViewMatrix(Camera * camera);
    void loadBlendFactor(float blendFactor);
    void loadFogColour(float r, float g, float b);
    
protected:
    virtual void getAllUniforms();
    virtual void bindAttributes();
    
private:
    int location_projectionMatrix;
    int location_viewMatrix;
    int location_modelMatrix;
    int location_fogColour;
    int location_cubeMap;
    int location_cubeMap2;
    int location_blendFactor;
    
    static std::string VERTEX_FILE;
    static std::string FRAGMENT_FILE;
};

#endif /* skyboxShader_h */

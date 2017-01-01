//
//  entity.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 14/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef entity_h
#define entity_h

#include <stdio.h>
#include "maths.h"
#include "Loader.h"
#include "viewStateCache.h"

class Particle;
class Entity {
public:
    
    Entity(Model* model, glm::vec3 position = glm::vec3(0, 0, 0), float rx = 0.0f, float ry = 0.0f, float rz = 0.0f, float scale = 1.0f, int textureIndex = 0);
    
    void increasePosition(float dx, float dy, float dz);
    void increaseRotation(float rx, float ry, float rz);
    void setRotation(float rx, float ry, float rz);
    void setPosition(float x, float y, float z);
    
    virtual void setViewMode(ViewMode viewMode = ViewMode::ThirdPerson){}
    
    glm::vec3 getPosition() { return _position; }
    
    
    int getTextureId() { return _textureIndex; }
    
    float getScale() { return _scale; }
    float getRotX() { return _rx; }
    float getRotY() { return _ry; }
    float getRotZ() { return _rz; }
    
    Model* getModel() { return _model; }
    
    ViewingState* getViewingMode() { return _viewingMode; }
    
    int ID()const{return m_ID;}
    
    Particle *getParticle() { return _particle; }
    
protected:
    Model *_model;
    glm::vec3 _position;
    float _rx, _ry, _rz;
    float _scale;
    int _textureIndex; // used for texture atlasing
    
    ViewingState* _viewingMode; // The way the camera should view the object if attached to the camera
    
    int m_ID;
    
    Particle *_particle = nullptr;
};

#endif /* entity_h */

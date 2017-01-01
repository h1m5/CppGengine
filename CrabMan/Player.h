//
//  Player.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 25/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include "movingentity.h"
#include "inputmanager.h"
#include "viewStateCache.h"

class Particle;
class Player : public MovingEntity {
public:
    /// Player
    Player(std::string modelName, std::string textureName = "", glm::vec3 position = glm::vec3(0,0,0), float rx=0, float ry=0, float rz=0, float scale=0.3, float mass = 10);
    void update(float dt);
    ViewingState *getViewMode() { return _viewingMode; }
    void setViewMode(ViewMode viewMode);
    
//    Particle *getParticle() { return _particle; }
    
private:
    void jump(float dt);
    void move(float dt);
    
    float currentMoveSpeed;
    float currentTurnSpeed;
    float acceleration;
    float upwardSpeed;
//    Particle *_particle;
};

#endif /* Player_h */

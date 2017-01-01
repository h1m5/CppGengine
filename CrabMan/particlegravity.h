//
//  particlegravity.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particlegravity_h
#define particlegravity_h

#include "maths.h"
#include "forcegenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
    glm::vec3 _gravity;
    ParticleGravity(){}
    ParticleGravity(const glm::vec3 &gravity)
    {
        _gravity = gravity;
    }
public:
    
    static ParticleGravity* sharedInstance()
    {
        static ParticleGravity instance = ParticleGravity(glm::vec3(0, -98, 0));
        
        return &instance;
    }
    
    virtual void updateForce(Particle *particle, float dt)
    {
        //        if(!particle->hasfiniteMass()) return
        
        if (_inputManager->isPressed(SDLK_f))
        {
            particle->addForce(_gravity * particle->getMass());
        }
    }
};

#endif /* particlegravity_h */

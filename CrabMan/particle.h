//
//  particle.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particle_h
#define particle_h

#include "maths.h"
#include <assert.h>
#include "statemachine.h"
#include "entity.h"
#include "inputmanager.h"

class Particle {
    
    StateMachine<Particle> *_stateMachine;
    
    Entity &_owner;
    
public:
    ///Particle
    Particle(Entity &owner, float mass);
    
    void addForce(const glm::vec3 &force);
    
    void update(float dt);
    
    StateMachine<Particle>* getFSM();
    
    float getMass() const;
    
    float getInverseMass() const;
    
    glm::vec3 getVelocity() const;
    
    glm::vec3 getPosition() const;
    
    glm::vec3 getAcceleration() const;
    
    void setVelocity(glm::vec3 velocity);
    
    void setPosition(glm::vec3 velocity);
    
    void clearAccumulator();
    
    void processInput();
    
    bool usegravity;
    
    glm::vec3 p_position;
    
    glm::vec3 p_velocity;
    
    glm::vec3 p_acceleration;
    
    glm::vec3 p_forceAccum;
    
    float p_damping;
    
    float p_inverseMass;
};

#endif /* particle_h */

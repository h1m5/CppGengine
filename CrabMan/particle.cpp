//
//  particle.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "particle.h"
#include "particleforceregistry.h"
#include "particlegravity.h"
#include "particledrag.h"
#include "particleworld.h"

Particle::Particle(Entity &owner, float mass) : _owner(owner)
{
    p_damping = 0.5f;
    
    p_inverseMass = 1.0 / mass;
    
    _stateMachine = new StateMachine<Particle>(this);
    
//    _stateMachine->setCurrentState(Gravity);
    
    usegravity = false;
    
    PhysicsWorld->addParticle(this);
}

void Particle::addForce(const glm::vec3 &force)
{
    p_forceAccum += force;
}

StateMachine<Particle>* Particle::getFSM()
{
    return _stateMachine;
}

void Particle::setVelocity(glm::vec3 velocity)
{
    p_velocity = velocity;
}

void Particle::setPosition(glm::vec3 position)
{
    p_position = position;
}

float Particle::getMass() const
{
    return 1.0 / p_inverseMass;
}

float Particle::getInverseMass() const
{
    return p_inverseMass;
}

glm::vec3 Particle::getVelocity() const
{
    return p_velocity;
}

glm::vec3 Particle::getPosition() const
{
    return p_position;
}

glm::vec3 Particle::getAcceleration() const
{
    return p_acceleration;
}

void Particle::update(float dt)
{
    assert(dt >= 0.0f);
    
//    _stateMachine->update();
    
    //processInput
    processInput();
    
    // update position;
    p_position += p_velocity * dt;
    _owner.setPosition(p_position.x, p_position.y, p_position.z);
    
    //calculate acceleration
    glm::vec3 resultingAcceleration = p_acceleration;
    resultingAcceleration = p_forceAccum * p_inverseMass;
    
    //update velocity
    p_velocity += resultingAcceleration * dt;
    
    //add damping
//    float dp = powf(p_damping, dt);
//    p_velocity *= dp;
    
    std::cout << "forceAccum: " << p_forceAccum.x << ", " <<p_forceAccum.y << ", " << p_forceAccum.z << std::endl;
    clearAccumulator();
    
    std::cout << "velocity: " << p_velocity.x << ", " << p_velocity.y << ", " << p_velocity.z << std::endl;
}

void Particle::processInput()
{
    float f = 240.0f;
    if (_inputManager->isPressed(SDLK_w)) {
        addForce(glm::vec3(0.0f, 0.0f, f));
    }
    if (_inputManager->isPressed(SDLK_s)) {
        addForce(glm::vec3(0.0f, 0.0f, -f));
    }
//    if (_inputManager->isPressed(SDLK_f)) {
//        usegravity = usegravity == true ? false : true;
//        _inputManager->releaseKey(SDLK_f);
//    }
}

void Particle::clearAccumulator()
{
    p_forceAccum = glm::vec3(0.0, 0.0, 0.0);
}

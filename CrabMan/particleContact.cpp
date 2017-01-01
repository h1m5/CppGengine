//
//  particleContact.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "particleContact.h"

void ParticleContact::resolve(float dt)
{
    resolveVelocity(dt);
    resolveInterpenetration(dt);
}

float ParticleContact::calculateSeparatingVelocity() const
{
    glm::vec3 relativeVelocity = particle[0]->getVelocity();
    if(particle[1]) relativeVelocity -= particle[1]->getVelocity();
    
    return glm::dot(relativeVelocity, contactNormal);
}

void ParticleContact::resolveVelocity(float dt)
{
    float separatingVelocity = calculateSeparatingVelocity();
    
    if (separatingVelocity > 0)
    {
        return;
    }
    
    float newSepVelocity = -separatingVelocity * restitution;
    
    glm::vec3 accCausedVelocity = particle[0]->getAcceleration();
    if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();
    float accCausedSepVelocity = glm::dot(accCausedVelocity, contactNormal*dt);
    
    if(accCausedSepVelocity < 0)
    {
        newSepVelocity += restitution * accCausedSepVelocity;
        
        if(newSepVelocity < 0) newSepVelocity = 0;
    }
    
    float deltaVelocity = newSepVelocity - separatingVelocity;
    
    float totalInverseMass = particle[0]->getInverseMass();
    
    if (particle[1]) totalInverseMass += particle[1]->getInverseMass();
    
    if (totalInverseMass <= 0) return;
    
    float impulse = deltaVelocity / totalInverseMass;
    
    glm::vec3 impulsePerIMass = contactNormal * impulse;
    
    particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerIMass * particle[0]->getInverseMass());
    
    if (particle[1])
    {
        particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerIMass * -particle[1]->getInverseMass());
    }
}

void ParticleContact::resolveInterpenetration(float dt)
{
    // If we don’t have any penetration, skip this step.
    if (penetration <= 0) return;
    
    // The movement of each object is based on its inverse mass, so
    // total that.
    float totalInverseMass = particle[0]->getInverseMass();
    if (particle[1]) totalInverseMass += particle[1]->getInverseMass();
    
    // If all particles have infinite mass, then we do nothing.
    if (totalInverseMass <= 0) return;
    
    // Find the amount of penetration resolution per unit of inverse mass.
    glm::vec3 movePerIMass = contactNormal * (-penetration / totalInverseMass);
    
    // Apply the penetration resolution.
    particle[0]->setPosition(particle[0]->getPosition() + movePerIMass * particle[0]->getInverseMass());
    
    if (particle[1])
    {
        particle[1]->setPosition(particle[1]->getPosition() + movePerIMass * particle[1]->getInverseMass());
    }
}

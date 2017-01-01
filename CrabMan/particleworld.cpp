//
//  particleworld.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 02/11/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "particleworld.h"
#include "particleforceregistry.h"
#include "particle.h"
#include "particlegravity.h"
#include "particledrag.h"
#include "particleContact.h"
#include "particleContactResolver.h"

ParticleWorld* ParticleWorld::sharedInstance()
{
    static ParticleWorld instance;
    
    instance.registry = ParticleForceRegistry::sharedInstance();
    
    instance.resolver = new ParticleContactResolver(0);
    return &instance;
}

void ParticleWorld::addParticle(Particle *particle)
{
    _particles.push_back(particle);
    ParticleForceRegistry::sharedInstance()->add(particle, ParticleGravity::sharedInstance());
    ParticleForceRegistry::sharedInstance()->add(particle, new ParticleDrag(3, 0.4));
}

void ParticleWorld::startFrame()
{
    for(Particle *p : _particles)
    {
        p->clearAccumulator();
    }
}

unsigned ParticleWorld::generateContacts()
{
    unsigned limit = maxContacts;
    ParticleContact *nextContact = contacts;
    
    auto *reg = firstContactGen;
    while (reg)
    {
        unsigned used = reg->gen->addContact(nextContact, limit);
        limit -= used;
        nextContact += used;

        if(limit <= 0) break;

        reg = reg->next;
    }
    
    return maxContacts - limit;
}

void ParticleWorld::integrate(float dt)
{
    for(Particle *p : _particles)
    {
        p->update(dt);
    }
}

void ParticleWorld::runPhysics(float dt)
{
    // First apply the force generators
    registry->updateForces(dt);
    
    // Then integrate the objects
    integrate(dt);
    
    // Generate contacts.
    unsigned usedContacts = generateContacts();
    
    // Process contacts
//    if(calculateIterations)
    if(true) resolver->setIterations(usedContacts * 2);
    resolver->resolveContacts(contacts, usedContacts, dt);
}

//unsigned ParticleContactGenerator::addContact(ParticleContact *contact, unsigned int limit)
//{
//    
//    contact->particle[0];
//    contact->particle[1];
//    
//    contact->contactNormal = glm::vec3(0, 1, 0);
//    
//    contact->penetration = 0.0;
//    contact->restitution = 0.1;
//    
//    return 1;
//}


















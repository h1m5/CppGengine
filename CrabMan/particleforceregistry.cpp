//
//  particleforceregistry.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "particleforceregistry.h"
#include "particle.h"
#include "forcegenerator.h"

ParticleForceRegistry* ParticleForceRegistry::sharedInstance()
{
    static auto instance = ParticleForceRegistry();
    
    return &instance;
}

void ParticleForceRegistry::add(Particle *particle, ParticleForceGenerator *fg)
{
    registrations.push_back(ParticleForceRegistration{particle, fg});
}

void ParticleForceRegistry::remove(Particle *particle, ParticleForceGenerator *fg)
{
    //This might not work. needs to be tested thoroughly
//    auto fr = ParticleForceRegistration{particle, fg};
//    auto it = std::find(registrations.begin(), registrations.end(), fr);
//    
//    if(it != registrations.end())
//    {
//        registrations.erase(it);
//    }
}

void ParticleForceRegistry::clear()
{
    registrations.clear();
}

void ParticleForceRegistry::updateForces(float duration)
{
    Registry::iterator i = registrations.begin();
    
    for (; i != registrations.end(); i++)
    {
        i->fg->updateForce(i->particle, duration);
    }
}
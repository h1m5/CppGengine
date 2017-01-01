//
//  particleCable.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/12/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "particleCable.h"
#include "particleContact.h"

unsigned ParticleCable::fillContact(ParticleContact *contact, unsigned int limit) const
{
    // Find the length of the cable
    float length = currentLength();
    
    // Check whether we're overextended
    if (length < maxLength)
    {
        return 0;
    }
    
    // Otherwise return the contact
    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];
    
    // Calculate the normal
    glm::vec3 normal = particle[1]->getPosition() - particle[0]->getPosition();
    normal = glm::normalize(normal);
    contact->contactNormal = normal;
    
    contact->penetration = length - maxLength;
    contact->restitution = restitution;
    
    return 1;
}

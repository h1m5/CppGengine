//
//  particleContactResolver.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 02/11/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "particleContactResolver.h"
#include "particleContact.h"

ParticleContactResolver::ParticleContactResolver(unsigned iterations)
{
    this->iterations = iterations;
}

void ParticleContactResolver::setIterations(unsigned int iterations)
{
    this->iterations = iterations;
}

void ParticleContactResolver::resolveContacts(ParticleContact *contactArray, unsigned int numContacts, float dt)
{
    iterationsUsed = 0;
    while(iterationsUsed < iterations)
    {
        float max = 0;
        unsigned maxIndex = numContacts;
        for(unsigned i = 0; i < numContacts; i++)
        {
            float sepVel = contactArray[i].calculateSeparatingVelocity();
            if (sepVel < max)
            {
                max = sepVel;
                maxIndex = i;
            }
            
        }
        contactArray[maxIndex].resolve(dt);
        
        iterations ++;
    }
}

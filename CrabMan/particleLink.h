//
//  particleLink.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/12/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particleLink_h
#define particleLink_h
#include "particle.h"
#include "maths.h"

class ParticleContact;
class ParticleLink {
    
public:
    Particle* particle[2];
    
protected:
    
    float currentLength() const
    {
        glm::vec3 relativePos = particle[0]->getPosition() - particle[1]->getPosition();
        return glm::length(relativePos);
    }
    
    virtual unsigned fillContact(ParticleContact *contact, unsigned limit) const = 0;
};

#endif /* particleLink_h */

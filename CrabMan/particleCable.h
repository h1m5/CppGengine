//
//  particleCable.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/12/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particleCable_h
#define particleCable_h

#include "particleLink.h"

class ParticleCable: public ParticleLink {
public:
    
    float maxLength;
    
    float restitution;
    
public:
    
    virtual unsigned fillContact(ParticleContact *contact, unsigned limit) const override;
};

#endif /* particleCable_h */

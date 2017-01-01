//
//  forcegenerator.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 24/08/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef forcegenerator_h
#define forcegenerator_h

#include <stdio.h>
#include "particle.h"

class ParticleForceGenerator {
public:
    
    virtual void updateForce(Particle *particle, float dt) = 0;
    
};



#endif /* forcegenerator_h */

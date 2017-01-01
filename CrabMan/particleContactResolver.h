//
//  particleContactResolver.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 02/11/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particleContactResolver_h
#define particleContactResolver_h

#include <stdio.h>

class ParticleContact;
class ParticleContactResolver
{
protected:
    
    //Holds the number of iterations allowed
    unsigned iterations;
    
    //Performance tracking value — keep record of the actual number of iterations used
    unsigned iterationsUsed;
    
public:
    ParticleContactResolver(unsigned iterations);
    
    void setIterations(unsigned iterations);
    
    void resolveContacts(ParticleContact *contactArray, unsigned numContacts, float dt);
};

#endif /* particleContactResolver_h */

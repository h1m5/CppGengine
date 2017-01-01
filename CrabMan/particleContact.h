//
//  particleContact.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particleContact_h
#define particleContact_h

#include "particle.h"

class ParticleContact
{
public:
    Particle* particle[2];
    
    float restitution;
    
    glm::vec3 contactNormal;
    
    
    void resolve(float dt);
    
    float calculateSeparatingVelocity() const;
    
    float penetration;
private:
    void resolveVelocity(float dt);
    
    
    void resolveInterpenetration(float dt);
};

#endif /* particleContact_h */

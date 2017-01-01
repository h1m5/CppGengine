//
//  movingparticle.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef movingparticle_h
#define movingparticle_h

#include "particle.h"

class movingParticle : public Particle
{
    glm::vec3 m_heading;
    glm::vec3 m_side;
    
    double m_maxSpeed;
};

#endif /* movingparticle_h */

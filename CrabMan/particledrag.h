//
//  particledrag.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particledrag_h
#define particledrag_h

#include "maths.h"
#include "forcegenerator.h"

/** 
 * a drag force defined by the equation
 *  drag = -p(k1|p| + k2|p|^2)
 */
class ParticleDrag : public ParticleForceGenerator
{
    /// Holds the velocity drag coefficient
    float _k1;
    
    /// Holds the velocity squared drag coefficient
    float _k2;
    
public:
    ParticleDrag(float k1, float k2)
    {
        _k1 = k1;
        _k2 = k2;
    }
    
    virtual void updateForce(Particle *particle, float dt)
    {
        glm::vec3 force = particle->getVelocity();
        
        float dragCoeff = glm::length(force);
        dragCoeff = (_k1 * dragCoeff) + (_k2 * (dragCoeff * dragCoeff));
        
        if (force.x != 0 || force.y != 0 || force.z != 0)
        {
            force = glm::normalize(force);
        }
        
        if (dragCoeff <= 0.1)
        {
            dragCoeff = 0.0f;
        }
        force *= -dragCoeff;
        std::cout << "drag: " << dragCoeff << std::endl;
        particle->addForce(force);
    }
};

#endif /* particledrag_h */

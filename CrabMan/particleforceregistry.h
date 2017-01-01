//
//  particleforceregistry.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particleforceregistry_h
#define particleforceregistry_h

#include <stdio.h>
#include <vector>

class Particle;
class ParticleForceGenerator;
class ParticleForceRegistry {
private:
    ParticleForceRegistry(){}
    
protected:
    struct ParticleForceRegistration
    {
        Particle *particle;
        ParticleForceGenerator *fg;
    };
    
    typedef std::vector<ParticleForceRegistration> Registry;
    Registry registrations;
    
public:
    
    static ParticleForceRegistry* sharedInstance();
    
    void add(Particle* particle, ParticleForceGenerator *fg);
    
    void remove(Particle* particle, ParticleForceGenerator *fg);
    
    /**
     * Clears all registrations from the registry. This will * not delete the particles or the force generators
     * themselves, just the records of their connection.
     */
    void clear();
    
    void updateForces(float duration);
};

#endif /* particleforceregistry_h */

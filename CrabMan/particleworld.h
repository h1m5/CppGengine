//
//  particleworld.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 02/11/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef particleworld_h
#define particleworld_h

#include <vector>

#define PhysicsWorld ParticleWorld::sharedInstance()

class Particle;
class ParticleForceRegistry;
class ParticleContactResolver;
class ParticleContact;

class ParticleContactGenerator
{
public:
    virtual unsigned addContact(ParticleContact *contact, unsigned limit) = 0;
};

class ParticleWorld {
    std::vector<Particle*> _particles;
//    std::vector<ParticleContact*> _contacts;
//    std::vector<ParticleContactGenerator*> _contactGenerators;
    
    ParticleWorld(){}
    ParticleWorld(const ParticleWorld &);
    ParticleWorld& operator=(const ParticleWorld &);
    
    ParticleContactResolver *resolver;
    
    ParticleForceRegistry *registry;
    
    
    struct ContactGenRegistration
    {
        ParticleContactGenerator *gen;
        ContactGenRegistration *next;
    };
    
    ContactGenRegistration *firstContactGen;
    
    ParticleContact *contacts;
    
    unsigned maxContacts;
    
public:
    
    static ParticleWorld* sharedInstance();
    
    void addParticle(Particle* particle);
    
    void startFrame();
    
    unsigned generateContacts();
    
    void integrate(float dt);
    
    void runPhysics(float dt);
};


#endif /* particleworld_h */

//
//  entityManager.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 20/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef entityManager_hpp
#define entityManager_hpp

#include <stdio.h>
#include <map>
#include "entity.h"
#include "telegram.h"

class EntityManager {
    typedef std::map<int, Entity*> EntityMap;
    
    EntityMap _entityMap;
    std::vector<Entity*> _entities;
    EntityManager(){}
    EntityManager(EntityManager &) {}
    EntityManager& operator=(const EntityManager&);
    
public:
    static EntityManager* instance();
    
    void registerEntity(Entity* e);
    
    Entity* getEntityByID(int id) const;
    
    std::vector<Entity*>& getEntities();
    
    void removeEntity(Entity* e);
    
};

#define EntityMgr EntityManager::instance()
#endif /* entityManager_hpp */

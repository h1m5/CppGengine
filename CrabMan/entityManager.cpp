//
//  entityManager.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 20/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "entityManager.hpp"

void EntityManager::registerEntity(Entity *e)
{
    _entityMap.insert(std::make_pair(e->ID(), e));
}

Entity* EntityManager::getEntityByID(int id) const {
    return _entityMap.at(id);
}

void EntityManager::removeEntity(Entity *e)
{
    _entityMap.erase(e->ID());
}

EntityManager* EntityManager::instance()
{
    static EntityManager *single = new EntityManager();
    
    return single;
}
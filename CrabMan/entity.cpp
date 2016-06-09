//
//  entity.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 14/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "entity.h"
#include "ResourceManager.h"

Entity::Entity(Model *model, glm::vec3 position, float rx, float ry, float rz, float scale, int textureIndex) : _viewingMode(ResourseManager::getViewState(ViewMode::ThirdPerson))
{
    _model = model;
    _position = position;
    _rx = rx;
    _ry = ry;
    _rz = rz;
    _scale = scale;
    _textureIndex = textureIndex;
}

void Entity::increasePosition(float dx, float dy, float dz){
    _position.x += dx;
    _position.y += dy;
    _position.z += dz;
}

void Entity::increaseRotation(float rx, float ry, float rz){
    _rx += rx;
    _ry += ry;
    _rz += rz;
}
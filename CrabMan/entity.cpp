//
//  entity.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 14/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "entity.h"
#include "ResourceManager.h"
#include "particle.h"

Entity::Entity(Model *model, glm::vec3 position, float rx, float ry, float rz, float scale, int textureIndex) : _viewingMode(ResourseManager::getViewState(ViewMode::ThirdPerson))
{
    m_ID = Maths::randomClamped();
    _model = model;
    _position = model->unitTranslation != nullptr ? *model->unitTranslation : position;
    _rx = rx;
    _ry = ry;
    _rz = rz;
    _scale = model->unitScale != nullptr ? *model->unitScale : scale;
    _textureIndex = textureIndex;
}

void Entity::setPosition(float x, float y, float z)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
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

void Entity::setRotation(float rx, float ry, float rz) {
    _rx = rx;
    _ry = ry;
    _rz = rz;
}

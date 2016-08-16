//
//  Player.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 25/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "Player.h"
#include "ResourceManager.h"
#include "loader.h"

Player::Player(std::string modelName, std::string textureName, glm::vec3 position, float rx, float ry, float rz, float scale)
: Entity(ResourseManager::getModel(modelName, textureName), position, rx, ry, rz, scale)
{
    currentMoveSpeed = 0.0f;
    currentTurnSpeed = 0.0f;
    acceleration = 300.0f;
    upwardSpeed = 0.0f;
    _viewingMode = ResourseManager::getViewState(ViewMode::ThirdPerson);
}

void Player::update(float dt)
{
    move(dt);
    jump(dt);
}

void Player::jump(float dt)
{
    upwardSpeed += -90.0f * dt;
    increasePosition(0, upwardSpeed * dt, 0);
    if(_position.y < 0){
        _position.y = 0;
        upwardSpeed = 0;
    }
}

void Player::move(float dt)
{
    if(_inputManager->isPressed(SDLK_w)){
        currentMoveSpeed += acceleration * dt;
    }
    if(_inputManager->isPressed(SDLK_s)){
        currentMoveSpeed += -acceleration * dt;
    }
    if(_inputManager->isPressed(SDLK_a)){
        currentTurnSpeed = Maths::interpolate(currentTurnSpeed, 900.0f, dt);
    }
    if(_inputManager->isPressed(SDLK_d)){
        currentTurnSpeed = Maths::interpolate(currentTurnSpeed, -900.0f, dt);
    }
    if(_inputManager->isPressed(SDLK_SPACE)){
        upwardSpeed = 40;
    }
    
    float distance = currentMoveSpeed * dt;
    float dx = distance * glm::sin(glm::radians(_ry));
    float dz = distance * glm::cos(glm::radians(_ry));
    
    increasePosition(dx, 0, dz);
    increaseRotation(0, currentTurnSpeed * dt, 0);
    
    currentMoveSpeed *= 0.9f;
    currentTurnSpeed *= 0.9f;
}

void Player::setViewMode(ViewMode viewMode)
{
    _viewingMode = ResourseManager::getViewState(viewMode);
}
//
//  camera3D.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "camera3D.h"
#include "maths.h"
#include "ResourceManager.h"
#include "FirstPersonViewState.h"
#include "thirdpersonviewstate.h"

Camera3D::Camera3D(Entity* referencePointObject, float rx, float ry, float rz)
: _pitch(rx), _yaw(ry), _roll(rz)
{
    _referencePointObject = referencePointObject;
    _worldUp = glm::vec3(0, 1, 0);
    _currentViewingState = referencePointObject->getViewingMode();
    _currentPitchRotationSpeed = 0.0f;
}

void Camera3D::update(float dt)
{
    checkInput(dt);
//    changeViewingState(_referencePointObject->getViewingMode());
    _currentViewingState->execute(this, dt);
    calculateFront();
    calculateRight();
    calculateUpDirection();
}

void Camera3D::checkInput(float dt)
{
    if(_inputManager->isPressed(SDLK_e)){
        _currentPitchRotationSpeed = Maths::interpolate(_currentPitchRotationSpeed, -10, dt);
    }
    if(_inputManager->isPressed(SDLK_q)){
        _currentPitchRotationSpeed = Maths::interpolate(_currentPitchRotationSpeed, 10, dt);
    }
    if(_inputManager->isPressed(SDLK_t)){
        if(_referencePointObject->getViewingMode()->currentViewModeID == ViewMode::ThirdPerson){
            _referencePointObject->setViewMode(ViewMode::FirstPerson);
            changeViewingState(_referencePointObject->getViewingMode());
        }else{
            _referencePointObject->setViewMode(ViewMode::ThirdPerson);
            changeViewingState(_referencePointObject->getViewingMode());
        }
        
        _inputManager->releaseKey(SDLK_t);
    }
    
    increaseRotation(_currentPitchRotationSpeed, 0, 0);
    
    if(_pitch > 85) _pitch = 85;
    if(_pitch < -85) _pitch = -85;
    
    _currentPitchRotationSpeed *= 0.9;
    
}
 
void Camera3D::changeViewingState(ViewingState* newState)
{
    assert(_currentViewingState && newState);
    _currentViewingState->exit(this);
    _currentViewingState = newState;
    _currentViewingState->enter(this);
}

void Camera3D::setRotation(float pitch, float yaw, float roll)
{
    _pitch = pitch;
    _yaw = yaw;
    _roll = roll;
}

glm::mat4 Camera3D::createViewMatrix()
{
    glm::mat4 vmatrix = glm::mat4();
    glm::vec3 center = _position + _front;
    vmatrix = glm::lookAt(_position, center, _up);
//    vmatrix = glm::rotate(vmatrix, _pitch, glm::vec3(1,0,0));
//    vmatrix = glm::rotate(vmatrix, _yaw, glm::vec3(0,1,0));
//    glm::vec3 pos = -_position;
//    vmatrix = glm::translate(vmatrix, pos);
    return vmatrix;
}

void Camera3D::calculateFront()
{
    _front.x = cosf(glm::radians(_yaw)) * cosf(glm::radians(_pitch));
    _front.y = glm::sin(glm::radians(-_pitch));
    _front.z = glm::cos(glm::radians(_pitch)) * glm::sin(glm::radians(_yaw));
    _front = glm::normalize(_front);
}

void Camera3D::calculateRight()
{
    _right = glm::cross(_front, _worldUp);
    _right = glm::normalize(_right);
}

void Camera3D::calculateUpDirection()
{
    _up = glm::cross(_right, _front);
    _up = glm::normalize(_up);
}
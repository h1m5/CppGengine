//
//  thirdpersonviewstate.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "thirdpersonviewstate.h"
#include "inputmanager.h"
#include "camera3D.h"
#include "maths.h"

void ThirdPersonViewState::execute(Camera3D *camera, float dt)
{
    checkInput();
    calculatePosition(camera, dt);
}

void ThirdPersonViewState::checkInput()
{
    if(_inputManager->isPressed(SDLK_x)){
        _distanceFromSubject++;
    }
    if(_inputManager->isPressed(SDLK_z)){
        if(_distanceFromSubject > _minDistanceFromSubject)
            _distanceFromSubject--;
    }
}

void ThirdPersonViewState::calculatePosition(Camera3D *camera, float dt)
{
    float horizontalDistance = _distanceFromSubject * glm::cos(glm::radians(camera->getPitch()));
    float verticalDistance = _distanceFromSubject * glm::sin(glm::radians(camera->getPitch())) + _yOffset;
    
    Entity* rf = camera->getReferencePointObject();
    
//    dt = 0.1;
    //calculate camera's position using horizontaldistance and verticaldistance
    float theta = rf->getRotY();
    float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
    float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));
    
    glm::vec3 newPosition = glm::vec3(rf->getPosition().x - offsetX,
                               rf->getPosition().y + verticalDistance,
                               rf->getPosition().z - offsetZ);
    doTransition(dt, newPosition);
    camera->setPosition(_deltaPosition);
//    camera->setPosition(newPosition);
    
    camera->setRotation(camera->getPitch(), 90 - rf->getRotY());
}

void ThirdPersonViewState::enter(Camera3D *camera)
{
    std::cout << "entering thirdperson view" << std::endl;
    
    _deltaPosition = camera->getPosition();
    _transitionSpeed = 0.06f;
}

void ThirdPersonViewState::exit(Camera3D *camera)
{
    std::cout << "exiting thirdperson view" << std::endl;
}

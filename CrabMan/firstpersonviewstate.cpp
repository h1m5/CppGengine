//
//  FirstPersonViewState.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "FirstPersonViewState.h"
#include "inputmanager.h"
#include "camera3D.h"
#include "maths.h"

void FirstPersonViewState::execute(Camera3D *camera, float dt)
{
//    camera->setPosition(camera->getReferencePointObject()->getPosition());
//    camera->setPosition(camera->getReferencePointObject()->getPosition().x,
//                        camera->getReferencePointObject()->getPosition().y + 4, //y offset of 5;
//                        camera->getReferencePointObject()->getPosition().z);
    
    glm::vec3 goal = glm::vec3(camera->getReferencePointObject()->getPosition().x,
                               camera->getReferencePointObject()->getPosition().y + 4, //y offset of 5;
                               camera->getReferencePointObject()->getPosition().z);
    
    checkInput();
    doTransition(dt, goal);
    camera->setPosition(_deltaPosition);
    
    
    camera->setRotation(camera->getPitch(),
                        -camera->getReferencePointObject()->getRotY()+90.0,
                        camera->getReferencePointObject()->getRotZ());
}

void FirstPersonViewState::checkInput()
{
    if(_inputManager->isPressed(SDLK_a) || _inputManager->isPressed(SDLK_d) || _inputManager->isPressed(SDLK_SPACE) || _inputManager->isPressed(SDLK_q) || _inputManager->isPressed(SDLK_e) || _inputManager->isPressed(SDLK_w) || _inputManager->isPressed(SDLK_s))
        _transitionSpeed = 1.0f;
    
}

void FirstPersonViewState::enter(Camera3D *camera)
{
    _deltaPosition = camera->getPosition();
    _transitionSpeed = 0.06f;
}

void FirstPersonViewState::exit(Camera3D *camera)
{
    
}

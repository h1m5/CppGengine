//
//  camera3D.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef camera3D_h
#define camera3D_h

#include <stdio.h>
#include "camera.h"
#include "entity.h"
#include "inputmanager.h"
#include "viewingState.h"
#include "firstpersonviewstate.h"
#include "thirdpersonviewstate.h"

class Camera3D : public Camera {
public:
    Camera3D(){}
    Camera3D(Entity *referencePointObject, float rx=0, float ry=0, float rz=0);
    
    virtual void update(float dt);
    void changeViewingState(ViewingState* newState);
    
    void increaseRotation(float x=0, float y=0, float z=0){
        _pitch += x;
        _yaw += y;
        _roll += z;
    }
    
    Entity* getReferencePointObject() { return _referencePointObject; }
    InputManager* getInputManager() { return _inputManager; }
    void setRotation(float pitch, float yaw, float roll=0.0);
    
    glm::mat4 createViewMatrix();
    float getPitch() { return _pitch; }
    float getYaw() { return _yaw; }
    float getRoll() { return _roll; }
    
//    ViewState getCurrentViewingState() { return _currentViewingState->getViewingState(); }
    
protected:
    Entity* _referencePointObject; // The object to which the camera is locked
    ViewingState *_currentViewingState;
    float _currentPitchRotationSpeed;
//    FirstPersonViewState *fps;
//    ThirdPersonViewState *tps;
    float _pitch;
    float _yaw;
    float _roll;
    
    glm::vec3 _front;
    glm::vec3 _right;
    glm::vec3 _worldUp;
    glm::vec3 _up;
    
    void calculateFront();
    void calculateRight();
    void calculateUpDirection();
    void checkInput(float dt);
    
};

#endif /* camera3D_h */

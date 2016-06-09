//
//  FirstPersonViewState.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef firstpersonviewstate_h
#define firstpersonviewstate_h

#include "viewingState.h"

class FirstPersonViewState: public ViewingState {
public:
    FirstPersonViewState():_currentPitchRotationSpeed(0.0f) {currentViewModeID = ViewMode::FirstPerson;}
    void execute(Camera3D* camera, float dt);
    void checkInput();
    void enter(Camera3D* camera);
    void exit(Camera3D* camera);
private:
    float _currentPitchRotationSpeed;
};

#endif /* firstpersonviewstate_h */

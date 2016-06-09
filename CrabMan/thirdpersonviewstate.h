//
//  thirdpersonviewstate.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef thirdpersonviewstate_h
#define thirdpersonviewstate_h

#include "viewingState.h"
#include "maths.h"

class ThirdPersonViewState: public ViewingState {
public:
    ThirdPersonViewState(): _yOffset(5){_distanceFromSubject = 20; currentViewModeID = ViewMode::ThirdPerson; _minDistanceFromSubject = 9; _transitionSpeed = 0.06;}
    void execute(Camera3D* camera, float dt);
    void checkInput();
    void enter(Camera3D* camera);
    void exit(Camera3D* camera);
    
private:
    float _angleAroundSubject;
    float _minDistanceFromSubject;
    float _yOffset;
    
    void calculatePosition(Camera3D* camera, float dt);
};

#endif /* thirdpersonviewstate_h */

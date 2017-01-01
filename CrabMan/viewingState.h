//
//  viewingState.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 27/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef viewingState_h
#define viewingState_h

#include "maths.h"
enum class ViewMode { FirstPerson, ThirdPerson };

class Camera3D;
class ViewingState {
protected:
    float _distanceFromSubject;
    glm::vec3 _deltaPosition;
    float _transitionSpeed;
    inline void doTransition(float dt, glm::vec3 goal){
        _deltaPosition = Maths::interpolate(_deltaPosition, goal, dt+_transitionSpeed);
    }
    
public:
    virtual void execute(Camera3D* camera, float dt) = 0;
    virtual void checkInput() = 0;
    virtual void enter(Camera3D* camera){}
    virtual void exit(Camera3D* camera){}
    ViewMode currentViewModeID;
};

#endif /* viewingState_h */

//
//  camera.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "maths.h"
#include "subscriber.h"

class Camera{
public:
    
    virtual glm::mat4 createViewMatrix() = 0;
    virtual void update(float dt) = 0;
    
    void increasePosition(float x=0, float y=0, float z=0){
        _position.x += x;
        _position.y += y;
        _position.z += z;
    }
    
    glm::vec3 getPosition() { return _position; }
    void setPosition(glm::vec3 position) { _position = position;}
    void setPosition(float x, float y, float z) { _position.x=x; _position.y=y; _position.z=z; }
    
protected:
    glm::vec3 _position;
};

#endif /* camera_h */

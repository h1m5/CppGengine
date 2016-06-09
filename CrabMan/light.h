//
//  light.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef light_h
#define light_h
#include "maths.h"

class Light{
public:
    Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation = glm::vec3(1, 0, 0))
    {
        _position = position;
        _color = color;
        _attenuation = attenuation;
    }
    
    void setPosition(float x, float y, float z) {
        _position.x = x;
        _position.y = y;
        _position.z = z;
    }
    
    glm::vec3 getPosition() { return _position; }
    
    void setColor(float x, float y, float z){
        _color.x = x;
        _color.y = y;
        _color.z = z;
    }
    
    glm::vec3 getColor() { return _color; }
    
    glm::vec3 getAttenuation() { return _attenuation; }
    
private:
    glm::vec3 _position;
    glm::vec3 _color;
    glm::vec3 _attenuation;
};

#endif /* light_h */

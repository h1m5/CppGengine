//
//  vehicle.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef vehicle_h
#define vehicle_h

#include "movingentity.h"

class Model;
class SteeringBehaviors;
class Vehicle : public MovingEntity
{
private:
    
    SteeringBehaviors* m_steering;
public:
    
    Vehicle(std::string modelName, std::string textureName = "", glm::vec3 position = glm::vec3(0,0,0), float rx=0, float ry=0, float rz=0, float scale=0.3, float mass = 1);
    void update(float dt);
    void setTarget(glm::vec3 target);
    void setTargetAgent1(Entity* e);
    void setTargetAgent2(Entity* e);
};

#endif /* vehicle_h */

//
//  steeringbehaviors.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef steeringbehaviors_h
#define steeringbehaviors_h

#include <stdio.h>
#include "maths.h"

class MovingEntity;
class SteeringBehaviors
{
    glm::vec3 seek(const glm::vec3 &targetPosition);
    glm::vec3 flee(const glm::vec3 &targetPosition);
    glm::vec3 arrive(const glm::vec3 &targetPosition, float deceleration);
    glm::vec3 pursue(MovingEntity* evader);
    glm::vec3 evade(MovingEntity* pursuer);
    glm::vec3 wander();
    
    MovingEntity *m_pEntity;
    glm::vec3 m_pTargetPosition;
    MovingEntity *m_pTargetEntity1;
    MovingEntity *m_pTargetEntity2;
    
    float m_dWanderRadius;
    float m_dWanderDistance;
    float m_dWanderJitter;
    
    glm::vec3 m_WanderTarget;
public:
    
    SteeringBehaviors(MovingEntity *owner);
    glm::vec3 calculate();
    glm::vec3 forwardComponent();
    glm::vec3 sideComponent();
    
    void setPath();
    void setTarget(glm::vec3 target);
    void setTargetAgent1(MovingEntity* v1);
    void setTargetAgent2(MovingEntity* v2);
    
    void seekOn();
    void fleeOn();
    void arriveOn();
    
    void seekOff();
    void fleeOff();
    void arriveOff();

};

#endif /* steeringbehaviors_h */

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
#define MIN_DETECTIONBOXLENGTH 3
#define MAX_SEEAHEAD 50.0f
#define MAX_AVOID_FORCE 20.0f
#define CIRCLE_RADIUS 26.0f
#define MAX_DISTANCE_AWAY 10000
#define POINT_SEEK_DISTANCE 20.0f

class Path;
class Entity;
class MovingEntity;
class SteeringBehaviors
{
    glm::vec3 seek(const glm::vec3 &targetPosition);
    glm::vec3 flee(const glm::vec3 &targetPosition);
    glm::vec3 arrive(const glm::vec3 &targetPosition, float deceleration = 3.0f);
    glm::vec3 pursue(MovingEntity* evader);
    glm::vec3 evade(MovingEntity* pursuer);
    glm::vec3 wander();
    glm::vec3 interpose(MovingEntity* agentA, MovingEntity* agentB);
    
    glm::vec3 obstacleAvoidance(std::vector<Entity*> &obstacles);
    Entity* findMostThreatheningObstatcle(const glm::vec3 &ahead1, const glm::vec3 &ahead2, const std::vector<Entity *> &obstacles);
    
    glm::vec3 hide(MovingEntity* target, std::vector<Entity*> &obstacles);
    glm::vec3 getHidingPosition(const glm::vec3 &obstaclePosition, const float obstacleRadius, const glm::vec3 &targetPosition);
    
    Path* _path;
    glm::vec3 followPath();
    
    MovingEntity *m_pEntity;
    glm::vec3 m_pTargetPosition;
    Entity *m_pTargetEntity1;
    Entity *m_pTargetEntity2;
    
    
    float m_dWanderRadius = 1.0f;
    float m_dWanderDistance = 0.5f;
    float m_dWanderJitter = 1.0f;
    float m_dBoxLength;
    
    glm::vec3 m_WanderTarget;
public:
    
    SteeringBehaviors(MovingEntity *owner);
    glm::vec3 calculate();
    glm::vec3 forwardComponent();
    glm::vec3 sideComponent();
    
    void setPath();
    void setTarget(glm::vec3 target);
    void setTargetAgent1(Entity* v1);
    void setTargetAgent2(Entity* v2);
    
    void seekOn();
    void fleeOn();
    void arriveOn();
    
    void seekOff();
    void fleeOff();
    void arriveOff();

};

#endif /* steeringbehaviors_h */

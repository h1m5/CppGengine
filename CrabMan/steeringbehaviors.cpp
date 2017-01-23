//
//  steeringbehaviors.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "steeringbehaviors.h"
#include "movingentity.h"
#include "entityManager.hpp"
#include "path.h"
#include <regex>

SteeringBehaviors::SteeringBehaviors(MovingEntity *owner)
{
    m_pEntity = owner;
//    _path = new Path(5, 0, 50, 0, 50);
    _path = new Path();
    _path->addPoint(-10, 0, -10);
    _path->addPoint(-10, 0, 10);
    _path->addPoint(10, 0, 10);
    _path->addPoint(10, 0, -10);
    _path->addPoint(0, 0, -30);
    _path->setStartPoint();
    _path->loopOn();
}

glm::vec3 SteeringBehaviors::calculate()
{
//    glm::vec3 totalForces = seek(m_pTargetPosition);
//    return seek(m_pTargetPosition);
    auto avoidance = obstacleAvoidance(EntityMgr->getEntities());
//    return flee(m_pTargetPosition);
//    return arrive(m_pTargetPosition, 5);
//    return pursue(m_pTargetEntity1);
    cout << avoidance.x << ", " << avoidance.y << ", " << avoidance.z << endl;
//    auto fleeForce = flee(m_pTargetPosition);
//    cout << fleeForce.x << ", " << fleeForce.y << ", " << fleeForce.z << endl;
//    return evade(m_pTargetEntity1);
//    return avoidance + seek(m_pTargetPosition);
    
//    return interpose(dynamic_cast<MovingEntity*>(m_pTargetEntity1), dynamic_cast<MovingEntity*>(m_pTargetEntity2));
//    return avoidance + hide(dynamic_cast<MovingEntity*>(m_pTargetEntity1), EntityMgr->getEntities());
//    return avoidance + wander();
    return followPath();
}

glm::vec3 SteeringBehaviors::seek(const glm::vec3 &targetPosition)
{
    glm::vec3 desiredVelocity = glm::normalize(targetPosition - m_pEntity->getPosition()) * m_pEntity->getMaxSpeed();
    
    return desiredVelocity - m_pEntity->getVelocity();
}

glm::vec3 SteeringBehaviors::flee(const glm::vec3 &targetPosition)
{
    // only flee if the target is within 'panic distance'.
    const float PanicDistanceSq = 30.0f;
    if (glm::distance(m_pEntity->getPosition(), m_pTargetPosition) > PanicDistanceSq) {
        auto stopVel = -m_pEntity->getVelocity() * 2.0f;
        return stopVel;
    }
    
    glm::vec3 desiredVelocity = glm::normalize(m_pEntity->getPosition() - targetPosition) * m_pEntity->getMaxSpeed();
    
    desiredVelocity.y = 0.0f;
    return desiredVelocity - m_pEntity->getVelocity();
}

glm::vec3 SteeringBehaviors::arrive(const glm::vec3 &targetPosition, float deceleration)
{
    glm::vec3 toTarget = targetPosition - m_pEntity->getPosition();
    
    //calculate the distance to the target position
    
    float dist = glm::length(toTarget);
    
    glm::vec3 desiredVelocity = toTarget;
    float slowingRadius = 100.0f;
        if (dist < slowingRadius){
            desiredVelocity = glm::normalize(desiredVelocity) * m_pEntity->getMaxSpeed() * (dist/slowingRadius);
        } else {
            desiredVelocity = glm::normalize(desiredVelocity) * m_pEntity->getMaxSpeed();
        }
    return desiredVelocity - m_pEntity->getVelocity();
    
//    if (dist < slowingRadius) {
//        const float decelerationTweaker = 0.3;
//        
//        // calculate the speed required to reach the target given the desired deceleration
//        float speed = dist / (deceleration * decelerationTweaker);
//        
//        // make sure the velocity does not exceed the max
//        speed = min(speed, m_pEntity->getMaxSpeed());
//        
//        // repeat seak
//        glm::vec3 desiredVelocity = (toTarget * speed) / dist;
//        
//        return desiredVelocity - m_pEntity->getVelocity();
//    } else {
//        glm::vec3 desiredVelocity = toTarget * m_pEntity->getMaxSpeed();
//        return desiredVelocity - m_pEntity->getVelocity();
//    }
}

float turnAroundTime(MovingEntity* agent, glm::vec3 targetPosition)
{
    auto toTarget = glm::normalize(targetPosition - agent->getPosition());
    
    float dot = glm::dot(agent->getHeading(), toTarget);
    
    const float coefficient = 0.5f;
    
    return (dot - 1.0f) * -coefficient;
}

glm::vec3 SteeringBehaviors::pursue(MovingEntity *evader)
{
    auto dist = evader->getPosition() - m_pEntity->getPosition();
    float T = glm::length(dist) / m_pEntity->getMaxSpeed();
    glm::vec3 futurePos = evader->getPosition() + evader->getVelocity() * T;
    return seek(futurePos);
    
//    // if the evader is ahead and facing the agent then seek the evader's current position
//    auto toEvader = evader->getPosition() - m_pEntity->getPosition();
//    
//    float relativeHeading = glm::dot(m_pEntity->getHeading(), evader->getHeading());
//    
//    if ( glm::dot(toEvader, m_pEntity->getHeading()) > 0 && relativeHeading < -0.95) {
////        return seek(evader->getPosition());
//        return arrive(evader->getPosition(), 5);
//    }
//    
//    // Not considered ahead so we predict where the evader will be.
//    // the look-ahead time is proportional to the distance between the evader
//    // and the pursuer; and is inversely proportional to the sum of
//    // the agents' velocities
//    
//    float lookAheadTime = toEvader.length() / (m_pEntity->getMaxSpeed() + 40.0f);
//    lookAheadTime += turnAroundTime(m_pEntity, evader->getPosition());
//
//    //now seek to the predicted future position of the evader
////    return seek(evader->getPosition() + evader->getVelocity() * lookAheadTime);
//    
//    return arrive(evader->getPosition() + evader->getVelocity() * lookAheadTime, 5);
}

glm::vec3 SteeringBehaviors::evade(MovingEntity *pursuer)
{
    glm::vec3 toPursuer = pursuer->getPosition() - m_pEntity->getPosition();
    
    float lookAheadTime = glm::length(toPursuer) / (m_pEntity->getMaxSpeed() + 40.0f);
    
    return flee(pursuer->getPosition() + pursuer->getVelocity() * lookAheadTime);
}

glm::vec3 SteeringBehaviors::wander()
{
    // add a smal random vector to the target's position
    m_WanderTarget += glm::vec3(Maths::randomClamped() * m_dWanderJitter, 0.0f, Maths::randomClamped() * m_dWanderJitter);

    m_WanderTarget = glm::normalize(m_WanderTarget);
    
    m_WanderTarget *= m_dWanderRadius;
    
    auto targetLocal = m_WanderTarget + glm::vec3(m_dWanderDistance, 0, m_dWanderDistance);
    
    auto targetWorld = Maths::pointToWorldSpace(targetLocal, m_pEntity->getHeading(), m_pEntity->getSide(), m_pEntity->getPosition());
    targetWorld.y = 0.0f;
//    return seek(targetLocal);
    return targetWorld - m_pEntity->getPosition();
}

glm::vec3 SteeringBehaviors::obstacleAvoidance(std::vector<Entity *> &obstacles)
{
    // the detection box length is proportional to the agent's velocity
    auto dynamicLength = glm::length(m_pEntity->getVelocity()) / m_pEntity->getMaxSpeed();
    
    auto ahead1 = m_pEntity->getPosition() + glm::normalize(m_pEntity->getVelocity()) * MAX_SEEAHEAD * dynamicLength;
//    auto ahead1 = m_pEntity->getPosition() + glm::normalize(m_pEntity->getVelocity()) * MAX_SEEAHEAD;
    auto ahead2 = m_pEntity->getPosition() + glm::normalize(m_pEntity->getVelocity()) * MAX_SEEAHEAD * 0.5f;
    
    auto mostThreatening = findMostThreatheningObstatcle(ahead1, ahead2, obstacles);
    glm::vec3 avoidance;
    
    if (mostThreatening != nullptr) {
        avoidance.x = ahead1.x - mostThreatening->getPosition().x;
        avoidance.z = ahead1.z - mostThreatening->getPosition().z;
        
        avoidance = glm::normalize(avoidance);
        avoidance *= MAX_AVOID_FORCE;
    } else {
        avoidance *= 0.0f;
    }
    
    return avoidance;
}

Entity* SteeringBehaviors::findMostThreatheningObstatcle(const glm::vec3 &ahead1, const glm::vec3 &ahead2, const std::vector<Entity *> &obstacles)
{
    Entity *mostThreatening = nullptr;
    for (int i=0; i<obstacles.size(); i++)
    {
        if (obstacles[i]->ID() == m_pTargetEntity1->ID() || obstacles[i]->ID() == m_pEntity->ID())
            continue;
        
        auto obstacle = obstacles[i];
        auto collision = Maths::lineIntersectionsCircle(ahead1, ahead2, m_pEntity->getPosition(), CIRCLE_RADIUS, obstacle->getPosition());
        
        if (collision && (mostThreatening == nullptr || glm::distance(m_pEntity->getPosition(), obstacle->getPosition()))) {
            mostThreatening = obstacle;
        }
    }
    return mostThreatening;
}

glm::vec3 SteeringBehaviors::interpose(MovingEntity* agentA, MovingEntity* agentB)
{
    glm::vec3 midPoint = (agentA->getPosition() + agentB->getPosition()) / 2.0f;
    
    float timeToReachMidPoint = glm::distance(m_pEntity->getPosition(), midPoint) / m_pEntity->getMaxSpeed();
    
    auto aPos = agentA->getPosition() + agentA->getVelocity() * timeToReachMidPoint;
    auto bPos = agentB->getPosition() + agentB->getVelocity() * timeToReachMidPoint;
    
    //calculate the midpoint of these predicted positions
    midPoint = (aPos + bPos) / 2.0f;
    
    return seek(midPoint);
}


glm::vec3 SteeringBehaviors::getHidingPosition(const glm::vec3 &obstaclePosition, const float obstacleRadius, const glm::vec3 &targetPosition)
{
    //calculate how far away the agent is to be from the chosen obstacle's bounding radius
    const float distanceFromBoundary = 20.0f;
    
    float distAway = obstacleRadius + distanceFromBoundary;
    
    //calculate the heading toward the object from the target
    auto toObs = glm::normalize(obstaclePosition - targetPosition);
    
    //scale it to size and add to the obstacle's position to get the hiding spot
    return (toObs * distAway) + obstaclePosition;
}

glm::vec3 SteeringBehaviors::hide(MovingEntity* target, std::vector<Entity*> &obstacles)
{
    float distToClosest = MAX_DISTANCE_AWAY;
    glm::vec3 bestHidingSpot;
    
    for(int i=0; i<obstacles.size(); i++)
    {
        if (obstacles[i]->ID() == m_pTargetEntity1->ID() || obstacles[i]->ID() == m_pEntity->ID())
            continue;
        //calculet the opsition of the hiding spot for this obstacle
        auto hidingSpot = getHidingPosition(obstacles[i]->getPosition(), CIRCLE_RADIUS, target->getPosition());
        
        //work in distance-squared space to find the closest hiding spot to the agent
        float dist = glm::distance2(hidingSpot, m_pEntity->getPosition());
        
        if(dist < distToClosest) {
            distToClosest = dist;
            bestHidingSpot = hidingSpot;
        }
    }
    
    // if no suitable obstacles found then evade the target
    if(distToClosest >= MAX_DISTANCE_AWAY) {
        return evade(target);
    }
    
    return seek(bestHidingSpot);
}

glm::vec3 SteeringBehaviors::followPath()
{
    //move to the next target if close enough to current target
    if(glm::distance2(_path->getCurrentPoint(), m_pEntity->getPosition()) < POINT_SEEK_DISTANCE) {
        _path->setNextPoint();
    }
    
    if (!_path->finished()) {
        return seek(_path->getCurrentPoint());
    }
    return glm::vec3(0);
//    else {
//        return seek(_path->getCurrentPoint());
//    }
}

void SteeringBehaviors::setTarget(glm::vec3 target)
{
    m_pTargetPosition = target;
}

void SteeringBehaviors::setTargetAgent1(Entity *v1)
{
    m_pTargetEntity1 = v1;
}

void SteeringBehaviors::setTargetAgent2(Entity *v2)
{
    m_pTargetEntity2 = v2;
}

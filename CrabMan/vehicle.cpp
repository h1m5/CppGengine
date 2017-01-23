//
//  vehicle.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 06/09/2016.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "vehicle.h"
#include "steeringbehaviors.h"
#include "ResourceManager.h"

Vehicle::Vehicle(std::string modelName, std::string texture, glm::vec3 position, float rx, float ry, float rz, float scale, float mass):
MovingEntity(ResourseManager::getModel(modelName, texture), position, rx, ry, rz, scale)
{
    m_steering = new SteeringBehaviors(this);
    m_mass = mass;
}

void Vehicle::update(float dt)
{
    glm::vec3 steeringForce = m_steering->calculate();
    
    glm::vec3 acceleration = steeringForce / (float)m_mass;
    
    m_velocity += acceleration * dt;
    
    // make sure vehicle does not exceed maximum velocity
    Maths::truncate(m_velocity, m_maxSpeed);
    
    _position += m_velocity * dt;
    
    if (m_velocity.length() > 0.001)
    {
        
        m_heading = m_velocity == glm::vec3(0.0) ? m_heading : glm::normalize(m_velocity);
        
//        std::cout << "\nheading: " << m_heading.x << ", " << m_heading.y << ", " << m_heading.z ;
//        std::cout << "\nvelocity: " << m_velocity.x << ", " << m_velocity.y << ", " << m_velocity.z ;
//        std::cout << "\nposition: " << _position.x << ", " << _position.y << ", " << _position.z << endl;
        
        auto ry = glm::degrees(atan2(m_heading.z, m_heading.x));
//        ry = 90 - ry;
//        std::cout << "\n roty: " << ry;
        setRotation(0, 90 - ry, 0);
        
        m_side = glm::cross(m_heading, glm::vec3(0, 1, 0));
    }
}

void Vehicle::setTarget(glm::vec3 target)
{
    m_steering->setTarget(target);
}

void Vehicle::setTargetAgent1(Entity* e)
{
    m_steering->setTargetAgent1(e);
}

void Vehicle::setTargetAgent2(Entity* e)
{
    m_steering->setTargetAgent2(e);
}

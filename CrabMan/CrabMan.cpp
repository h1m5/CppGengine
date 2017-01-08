//
//  CrabMan.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "CrabMan.h"
#include "Loader.h"
#include "ResourceManager.h"
#include "fontrenderer.h"
#include "particle.h"
#include "particleforceregistry.h"
#include "particlegravity.h"
#include "particleworld.h"
#include "vehicle.h"

CrabMan::CrabMan()
{
    init();
}

void CrabMan::init()
{
    _window = new Window;
    _window->create("The Crab", 1024, 640, RESIZABLE);
    _window->registerSubscriber(this);
    _window->registerSubscriber(InputManager::getInstance());
    
    gameState = STATE::PLAY;
    
    _timeKeeper = new FpsLimiter();
    createGameObjects();
    
    enterLoop();
}

void CrabMan::createGameObjects()
{
    renderer = new EntityRenderer("res/lighting");
    _window->registerSubscriber(renderer);
    
    Entity *e1 = new Entity(ResourseManager::getModel("res/field.obj", ""), glm::vec3(-10,-2.5,0), 0,0,0, 2);
    _entities.push_back(e1);
    
//    aPlayer = new Player("res/nanosuit/nanosuit.obj", "", glm::vec3(0,0,0), 0,180,0, 0.5);
//    aPlayer = new Player("res/dice/Dice_high_poly.obj", "", glm::vec3(0,0,0), 0,0,0, 2);
    aPlayer = new Player("res/person.obj", "res/playerTexture.png", glm::vec3(-5,0,0), 0,0,0, 1);
    
//    agent = new Vehicle("res/nanosuit/nanosuit.obj", "", glm::vec3(10,0,8), 0,0,0, 1);
    agent = new Vehicle("res/cube.obj", "", glm::vec3(10,0,8), 0,0,0, 5);
    
    agent->setTargetAgent1(aPlayer);
    
    _entities.push_back(aPlayer);
    _entities.push_back(agent);
    
    camera = new Camera3D(aPlayer, 30);
    Light *light0 = new Light(glm::vec3(10,700,10), glm::vec3(0.5, 0.6, 0.7));
    Light *light1 = new Light(glm::vec3(-10,10,-10), glm::vec3(0.5, 0.6, 0.7), glm::vec3(1.0f, 0.01f, 0.002f));
    lights.push_back(light0);
    lights.push_back(light1);
    
    FontRenderer::sharedInstance()->init("res/textShader", "res/fonts/bubblegum.ttf");
    
    skyBoxRenderer = new SkyboxRenderer(renderer->getProjectionMatrix());
}

void CrabMan::enterLoop()
{
    while(gameState != STATE::QUIT){
        _timeKeeper->begin();
        
        PhysicsWorld->startFrame();
        
        runGraphicsUpdate();
        
//        PhysicsWorld->runPhysics(_timeKeeper->getDeltaTime());
        aPlayer->update(_timeKeeper->getDeltaTime());
        agent->setTarget(aPlayer->getPosition());
        agent->update(_timeKeeper->getDeltaTime());
        
        _window->update();
        _timeKeeper->end();
    }
}

void CrabMan::runGraphicsUpdate()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(Entity *e : _entities) {
        if(e->getViewingMode()->currentViewModeID == ViewMode::ThirdPerson)
            renderer->render(e, camera, lights);
    }
    
    skyBoxRenderer->render(camera);
    
    auto fps = std::to_string(roundf(_timeKeeper->getFPS())).erase(4);
    FontRenderer::sharedInstance()->renderText(fps+" fps", 0.0f, 5.0f, 0.4f, glm::vec3(0.9f, 0.0f, 0.1f));
    
    camera->update(_timeKeeper->getDeltaTime());
}

void CrabMan::update(SDL_Event *ev)
{
    switch (ev->type) {
        case SDL_QUIT: gameState = STATE::QUIT; break;
        default: break;
    }
}

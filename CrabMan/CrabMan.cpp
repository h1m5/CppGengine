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
    
    Entity *e1 = new Entity(ResourseManager::getModel("res/field.obj", ""), glm::vec3(-10,-1.5,0), 0,0,0, 1);
    _entities.push_back(e1);
//    aPlayer = new Player("nanosuit/nanosuit.obj", "", glm::vec3(0,0,0), 0,180,0, 0.5);
    aPlayer = new Player("res/dice/Dice_high_poly.obj", "", glm::vec3(0,0,0), 0,0,0, 2);
    _entities.push_back(aPlayer);
    
    camera = new Camera3D(aPlayer, 30);
    light0 = new Light(glm::vec3(10,10,10), glm::vec3(0.5, 0.6, 0.7), glm::vec3(1.0f, 0.01f, 0.002f));
    Light *light1 = new Light(glm::vec3(-10,10,-10), glm::vec3(0.5, 0.6, 0.7), glm::vec3(1.0f, 0.01f, 0.002f));
    lights.push_back(light0);
    lights.push_back(light1);
    
    skbRenderer = new SkyboxRenderer(renderer->getProjectionMatrix());
}

void CrabMan::enterLoop()
{
    while(gameState != STATE::QUIT){
        _timeKeeper->begin();
        
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        aPlayer->update(_timeKeeper->getDeltaTime());
        for(Entity *e : _entities) {
            if(e->getViewingMode()->currentViewModeID == ViewMode::ThirdPerson)
                renderer->render(e, camera, lights);
        }
        
        skbRenderer->render(camera);
        
         camera->update(_timeKeeper->getDeltaTime());
        _window->update();
        std::cout << "Frame rate: " << _timeKeeper->end() << std::endl;
    }
}

void CrabMan::update(SDL_Event *ev)
{
    switch (ev->type) {
        case SDL_QUIT: gameState = STATE::QUIT; break;
        default: break;
    }
}
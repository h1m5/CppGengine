//
//  CrabMan.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef CrabMan_h
#define CrabMan_h

#include "DisplayManager.h"
#include "entityrenderer.h"
#include "camera3D.h"
#include "inputmanager.h"
#include "Timing.hpp"
#include "Player.h"
#include <vector>
#include "skyboxRenderer.h"
#include "particleforceregistry.h"
#include "particledrag.h"

enum class STATE { PLAY, QUIT };

class Vehicle;
class CrabMan : public Subscriber{
public:
    CrabMan();
    void enterLoop();
    void update(SDL_Event *ev);
    
private:
    void init();
    void createGameObjects();
    void runGraphicsUpdate();
    
    STATE gameState;
    Window *_window;
    EntityRenderer *renderer;
    SkyboxRenderer *skyBoxRenderer;
    Camera3D *camera;
    FpsLimiter* _timeKeeper;
    std::vector<Light*> lights;
    Model *aModel;
    Model *plane;
    Player *aPlayer;
    Vehicle *agent;
    std::vector<Entity*> _entities;
};

#endif /* CrabMan_h */

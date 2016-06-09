//
//  Timing.hpp
//  GraphicsTutorial
//
//  Created by Imhoisili Otokhagua on 21/07/15.
//  Copyright © 2015 TriKomand. All rights reserved.
//

#ifndef Timing_cpp
#define Timing_cpp

#include <SDL2/SDL.h>

class FpsLimiter
{
public:
    FpsLimiter();
    void init(float maxFPS);
    
    void setMaxFPS(float maxFPS);
    
    void begin();
    
    // end will return the current FPS
    float end();
    
    static float getDeltaTime() {return _deltaTime;}
    
private:
    
    void calculateFPS();
    
    float _fps;
    float _maxFPS;
    float _frameTime;
    static float _deltaTime;
    unsigned int _startTicks;
    
};

#endif /* Timing_cpp */

//
//  Timing.cpp
//  GraphicsTutorial
//
//  Created by Imhoisili Otokhagua on 21/07/15.
//  Copyright © 2015 TriKomand. All rights reserved.
//

#include "Timing.hpp"
#include <iostream>

float FpsLimiter::_deltaTime = 0.0f;

FpsLimiter::FpsLimiter()
{
    init(0.0f);
}

void FpsLimiter::init(float maxFPS)
{
    setMaxFPS(maxFPS);
}

void FpsLimiter::setMaxFPS(float maxFPS)
{
    if(maxFPS <= 0){
        _maxFPS = 60;
    } else {
        _maxFPS = maxFPS;
    }
}

void FpsLimiter::begin()
{
    _startTicks = SDL_GetTicks();
}

float FpsLimiter::end()
{
    calculateFPS();
    float frameTicks = SDL_GetTicks() - _startTicks;
    //Limit the FPS to the max FPS
    if(1000.0f / _maxFPS > frameTicks) {
        SDL_Delay(1000.0f / _maxFPS - frameTicks);
    }

    return _fps;
}

void FpsLimiter::calculateFPS()
{
    static const int NUM_SAMPLES = 100;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;
    
    //get current and previous Ticks
    static float prevTicks = SDL_GetTicks(); //SDL_GetTicks get the current time in milliseconds since SDL was initialized
    float currentTicks;
    currentTicks = SDL_GetTicks();
    
    _frameTime = currentTicks - prevTicks;
    prevTicks = currentTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
//    _deltaTime = _frameTime/1000.0f;
    
    int count;
    
    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }
    
    float frameTimeAverage = 0;
    for (int i = 0; i < count;  i++) {
        frameTimeAverage += frameTimes[i];
    }
    
    frameTimeAverage /= count;
    _deltaTime = frameTimeAverage / 1000.0f;
    
    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
//        _deltaTime = 1.0f/_fps;
    } else {
        _fps = 60;
    }
}
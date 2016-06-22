//
//  DisplayManager.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef DisplayManager_h
#define DisplayManager_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include "publisher.h"

enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZABLE = 0x8};
class Window : public Publisher {
public:
    Window();
    ~Window();
    
    int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
    
    int getScreenWidth() { return _screenWidth; }
    int getScreenHeight() { return _screenHeight; }
    
    static int getWidth(){return _screenWidth;}
    static int getHeight(){return _screenHeight;}
    
    void update();
    void resizeGL(const SDL_Event &ev);
private:
    void swapBuffer();
    void notifySubscribers();
    SDL_Window* _sdlWindow;
    static int _screenWidth;
    static int _screenHeight;
};

#endif /* DisplayManager_h */

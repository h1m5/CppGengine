//
//  DisplayManager.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "DisplayManager.h"

int Window::_screenWidth = 0;
int Window::_screenHeight = 0;

Window::Window()
{
    
}

Window::~Window()
{
    
}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
{
    Uint32 flags = SDL_WINDOW_OPENGL;
    
    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }
    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }
    if (currentFlags & RESIZABLE) {
        flags |= SDL_WINDOW_RESIZABLE;
    }
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    
    _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
    
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    
    if(_sdlWindow == nullptr){
//        fatalError("SDL Window could not be created!");
    }
    
    SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
    if(glContext == nullptr){
//        fatalError("SDL_GL_Context could not be created");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        glContext = SDL_GL_CreateContext(_sdlWindow);
        
        if (glContext == nullptr) {
            printf("couldn't create GL_CONTEXT");
            exit(1);
        }
    }
    
    glewExperimental = true;
    GLenum error = glewInit();
    if(error != GLEW_OK){
//        fatalError("GLEW could not be initialized");
    }
    
    //Check the Opengl Version
    printf("***    OpenGL Version: %s ***\n", glGetString(GL_VERSION));
    
    SDL_GL_SetSwapInterval(1);
    
    glViewport(0, 0, _screenWidth, _screenHeight);
    return 0;
}

void Window::notifySubscribers()
{
    SDL_Event ev;
    
    while (SDL_PollEvent(&ev)){
        resizeGL(ev);
        for(std::list<Subscriber*>::const_iterator i=subscribers.begin(); i!=subscribers.end(); i++){
            (*i)->update(&ev);
        }
    }
}

void Window::resizeGL(const SDL_Event &ev)
{
    if(ev.type == SDL_WINDOWEVENT){
        if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
            _screenWidth = ev.window.data1;
            _screenHeight = ev.window.data2;
        }
    }
}

void Window::update(){
    notifySubscribers();
    swapBuffer();
}

void Window::swapBuffer()
{
    SDL_GL_SwapWindow(_sdlWindow);
}

//
//  inputmanager.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 14/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef inputmanager_hpp
#define inputmanager_hpp

#include <stdio.h>
#include <map>
#include "publisher.h"
#define _inputManager InputManager::getInstance()

class InputManager : public Subscriber{
public:
    ~InputManager(){}
    
    void pressKey(unsigned int key)
    {
        _keyMap[key] = true;
    }
    
    void releaseKey(unsigned int key)
    {
        _keyMap[key] = false;
    }
    
    bool isPressed(unsigned int key)
    {
        auto it = _keyMap.find(key);
        
        if(it != _keyMap.end())
            return it->second;
        
        return false;
    }
    
    void update(SDL_Event *ev){
        switch(ev->type){
            case SDL_KEYDOWN: pressKey(ev->key.keysym.sym); break;
            case SDL_KEYUP:
                releaseKey(ev->key.keysym.sym); break;
        }
    }
    
    static InputManager *getInstance() {
        
        if(!_instance)
            _instance = new InputManager();
        
        return _instance;
    }
    
private:
    std::map<unsigned int, bool> _keyMap;
    InputManager(){}
    
    InputManager(Publisher * publisher){
        publisher->registerSubscriber(this);
    }
    
    static InputManager *_instance;
};

#endif /* inputmanager_hpp */

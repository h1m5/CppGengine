//
//  state.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 25/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef statemachine_h
#define statemachine_h

#include <stdio.h>
#include <assert>
#include "state.h"

template <class entity_type>
class StateMachine {
public:
    StateMachine(entity_type *owner):
    _owner(owner),
    _currentState(NULL),
    _previousState(NULL),
    _globalState(NULL)
    {}
    
    virtual void Execute() = 0;
    
    void setCurrentState(State<entity_type>* s){
        _currentState = s;
    }
    void setPreviousState(State<entity_type>* s){
        _previousState = s;
    }
    void setGlobalState(State<entity_type>* s){
        _globalState = s;
    }
    
    void update()const {
        if(_globalState) _globalState->execute(_owner);
        
        if(_currentState) _currentState->execute(_owner);
    }
    
    void changeState(State<entity_type>* newState){
        assert(newState && "<StateMachine::changeState()>::trying to change to a null state");
        
        _previousState = _currentState;
        _currentState->exit(_owner);
        _currentState = newState
        _currentState->enter(_owner);
    }
    
    void revertToPreviousState(){
        changeState(_previousState);
    }
    
    State<entity_type>* getCurrentState() const { return _currentState; }
    State<entity_type>* getPreviousState() const { return _previousState; }
    State<entity_type>* getGlobalState() const { return _globalState; }
    
private:
    entity_type *_owner;
    
    State<entity_type> *_currentState;
    State<entity_type> *_previousState;
    State<entity_type> *_globalState;
};

#endif /* statemachine_h */

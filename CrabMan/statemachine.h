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

template <class Q>
class StateMachine {
public:
    StateMachine(Q *owner):
    _owner(owner),
    _currentState(NULL),
    _previousState(NULL),
    _globalState(NULL)
    {}
    
    virtual void Execute() = 0;
    
    void setCurrentState(State<Q>* s){
        _currentState = s;
    }
    void setPreviousState(State<Q>* s){
        _previousState = s;
    }
    void setGlobalState(State<Q>* s){
        _globalState = s;
    }
    
    void update()const {
        if(_globalState) _globalState->execute(_owner);
        
        if(_currentState) _currentState->execute(_owner);
    }
    
    void changeState(State<Q>* newState){
        assert(newState && "<StateMachine::changeState()>::trying to change to a null state");
        
        _previousState = _currentState;
        _currentState->exit(_owner);
        _currentState = newState
        _currentState->enter(_owner);
    }
    
    void revertToPreviousState(){
        changeState(_previousState);
    }
    
    State<Q>* getCurrentState() const { return _currentState; }
    State<Q>* getPreviousState() const { return _previousState; }
    State<Q>* getGlobalState() const { return _globalState; }
    
private:
    Q *_owner;
    
    State<Q> *_currentState;
    State<Q> *_previousState;
    State<Q> *_globalState;
};

#endif /* statemachine_h */

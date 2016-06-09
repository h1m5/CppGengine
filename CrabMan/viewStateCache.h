//
//  viewStateCache.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 28/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef viewStateCache_h
#define viewStateCache_h

#include "firstpersonviewstate.h"
#include "thirdpersonviewstate.h"
#include <map>

class ViewingStateCache {
public:
    
    ViewingState* getViewMode(ViewMode mode){
        auto vit = _viewStatesCache.find(mode);
        
        if(vit == _viewStatesCache.end()){
            ViewingState* newState;
            if (mode == ViewMode::FirstPerson){
                newState = new FirstPersonViewState();
            } else if (mode == ViewMode::ThirdPerson){
                newState = new ThirdPersonViewState();
            }
            _viewStatesCache.insert(make_pair(mode, newState));
            return newState;
        }
        
        return vit->second;
    }
    
private:
    std::map<ViewMode, ViewingState*> _viewStatesCache;
};

#endif /* viewStateCache_h */

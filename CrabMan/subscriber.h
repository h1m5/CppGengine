//
//  subscriber.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef subscriber_h
#define subscriber_h
#include <SDL2/SDL.h>

class Subscriber {
public:
    virtual void update(SDL_Event *ev) = 0;
//    virtual void update(float dt) = 0;
};

#endif /* subscriber_h */

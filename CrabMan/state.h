//
//  state.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 25/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef state_h
#define state_h

#include <stdio.h>

class State {
public:
    virtual void Execute() = 0;
};

#endif /* state_h */

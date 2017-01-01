//
//  state.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 18/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef state_h
#define state_h
#include "telegram.h"

template <class Q>
class State {
public:
    virtual void enter(Q*){};
    virtual void execute(Q*)=0;
    virtual void exit(Q*){};
    
    virtual ~State(){}
    
    virtual bool onMessage(Q*, const Telegram&) { return false; }
};

#endif /* state_h */

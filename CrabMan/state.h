//
//  state.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 18/06/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef state_h
#define state_h

template <class entity_type>
class State {
public:
    virtual void enter(entity_type*)=0;
    virtual void execute(entity_type*)=0;
    virtual void exit(entity_type*)=0;
    
    virtual ~State(){}
};

#endif /* state_h */

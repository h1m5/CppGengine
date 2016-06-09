//
//  publisher.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef publisher_h
#define publisher_h
#include <list>
#include "subscriber.h"

class Publisher {
public:
    void registerSubscriber(Subscriber *s){
        subscribers.push_back(s);
    }
    void unsubcribe(Subscriber* s){
        subscribers.remove(s);
    }
    virtual void notifySubscribers() = 0;
    
    std::list<Subscriber*> subscribers;
};

#endif /* publisher_h */

//
//  messageDispatcher.hpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 07/07/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef messageDispatcher_hpp
#define messageDispatcher_hpp

#include <stdio.h>
#include <set>
#include "telegram.h"
#include "entity.h"

class MessageDispatcher {
    std::set<Telegram> _priorityQ;
    
    void discharge(Entity *p_receiver, const Telegram& msg);
    
    MessageDispatcher(){}
    
public:
    
    static MessageDispatcher* instance();
    
    void dispatchMessage(double delay, int sender, int receiver, int message, void* extraInfo);
    
    void dispatchDelayedMessages();
};


#define Dispatch MessageDispatcher::instance();
#endif /* messageDispatcher_hpp */

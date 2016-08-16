//
//  messageDispatcher.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 07/07/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include "messageDispatcher.hpp"

void MessageDispatcher::discharge(Entity *p_receiver, const Telegram &msg)
{
    
}

void MessageDispatcher::dispatchMessage(double delay, int sender, int receiver, int message, void *extraInfo)
{
    
}

void MessageDispatcher::dispatchDelayedMessages()
{
    
}

MessageDispatcher* MessageDispatcher::instance()
{
    static MessageDispatcher *single = new MessageDispatcher();
    
    return single;
}


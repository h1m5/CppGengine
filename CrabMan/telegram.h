//
//  telegram.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 07/07/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef telegram_h
#define telegram_h

struct Telegram {
    int sender;
    int receiver;
    int msg;
    double dispatchTime;
    void* extraInfo;
};

#endif /* telegram_h */

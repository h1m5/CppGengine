//
//  main.cpp
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 12/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#include <iostream>
#include "CrabMan.h"
#include "ResourceManager.h"

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::string argv_str(argv[0]);
//    std::string base = argv_str.substr(0, argv_str.find_last_of("/"));
//    ResourseManager::workingDirectory = base;
    
    CrabMan *cr = new CrabMan();
    
    cr->enterLoop();
    return 0;
}

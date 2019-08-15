//
//  Dashboard.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Dashboard_hpp
#define Dashboard_hpp

#include <stdio.h>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Renderer.hpp"
#include "Vehicle.hpp"
#include "CB650F.hpp"

class Dashboard {
    Renderer *r;
    Vehicle *vehicle;
    
    FontWrapper *hnproMedium27;
    FontWrapper *hnproHuge;
    FontWrapper *hnproMediumOblique;
    FontWrapper *hnproHugeOblique;
    FontWrapper *hnproExtraHeavy36;
public:
    Dashboard(Renderer &r);
    void render();
};

#endif /* Dashboard_hpp */

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
#include <map>
#include FT_FREETYPE_H
#include "Renderer.hpp"
#include "Vehicle.hpp"
#include "CB650F.hpp"
#include "honda_generated.h"
#include "ECUConnector.hpp"
#include "Definitions.h"

class Dashboard {
    Renderer *r;
    Vehicle *vehicle;
    
    GLuint squareTextureId;
    GLuint screenTexture;
    GLuint frameBuffer;
    
    std::map<std::string, float> attrX;
    
    ECUConnector *connector;
    
    FontWrapper *hnproMedium27;
    FontWrapper *hnproHuge;
    FontWrapper *hnproMediumOblique;
    FontWrapper *hnproHugeOblique;
    FontWrapper *hnproExtraHeavy36;
    
    void createFramebuffer();
public:
    Dashboard(Renderer &r);
    void render();
    void renderFixed();
};

#endif /* Dashboard_hpp */

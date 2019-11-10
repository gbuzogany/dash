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
#include <thread>
#include FT_FREETYPE_H
#include "Renderer.hpp"
#include "Vehicle.hpp"
#include "CB650F.hpp"
#include "honda_generated.h"
#include "ECUConnector.hpp"
#include "Definitions.h"

typedef struct {
    std::string title;
    std::string artist;
    std::string album;
} DashMediaItem;

class Dashboard {
    Renderer *r;
    Vehicle *vehicle;
    
    GLuint squareTextureId;
    GLuint screenTexture;
    GLuint frameBuffer;
    
    std::string playStatus_;
    DashMediaItem nowPlaying_;
    
    std::thread mediaServiceThread;
    
    std::map<std::string, float> attrX;
    
    ECUConnector *connector;
    
    FontWrapper *hnproMedium27;
    FontWrapper *hnproHuge;
    FontWrapper *hnproMediumOblique;
    FontWrapper *hnproHugeOblique;
    FontWrapper *hnproExtraHeavy36;
    
    void createFramebuffer();
    void startMediaService();
public:
    Dashboard(Renderer &r);
    void render();
    void renderFixed();
    
    void setPlayStatus(std::string playStatus);
    void setNowPlaying(DashMediaItem mediaItem);
};

#endif /* Dashboard_hpp */

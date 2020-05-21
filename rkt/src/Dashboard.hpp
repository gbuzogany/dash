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
#include <queue>
#include FT_FREETYPE_H
#include "Scene.hpp"
#include "Vehicle.hpp"
#include "Definitions.h"
#include "Animation.hpp"
#include "Utils.hpp"

typedef struct {
    std::string title;
    std::string artist;
    std::string album;
} DashMediaItem;

class Dashboard : Scene {
    Vehicle *vehicle;
    
    GLuint arcTextureId;
    GLuint squareTextureId;
    GLuint fasterTexture;
    
    GLuint screenTexture;
    GLuint frameBuffer;
    
    std::map<std::string, float> attrX;
    std::queue<Animation*> animationQueue;
    
    FontWrapper *hnproSmall;
    FontWrapper *hnproMedium27;
    FontWrapper *hnproHuge;
    FontWrapper *hnproMediumOblique;
    FontWrapper *hnproHugeOblique;
    FontWrapper *hnproExtraHeavy36;
    
    void createFramebuffer();
public:
    Dashboard(Renderer *r, RocketteServiceImpl *service);

    void render();
    void renderFixed();
    bool update(float delta);
    
    void setPlayStatus(std::string playStatus);
    void setNowPlaying(DashMediaItem mediaItem);
    void drawCounter(FontWrapper &font, GLfloat x, GLfloat y, GLfloat radius, GLfloat longTickLength, GLfloat shortTickLength, GLfloat startAngle, GLfloat endAngle, GLfloat maxValue, GLfloat beginCritical, GLint ticksBetweenInts);
    void drawNeedle(float value, float maxValue, GLint x, GLint y, GLfloat tipRadius, GLfloat bottomRadius, GLfloat startAngle, GLfloat endAngle);
};

#endif /* Dashboard_hpp */

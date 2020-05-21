//
//  MainScene.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include <iostream>
#include <ft2build.h>
#include <map>
#include <thread>
#include <queue>
#include FT_FREETYPE_H
#include "Scene.hpp"
#include "Definitions.h"
#include "Animation.hpp"
#include "Utils.hpp"

class MainScene : Scene {
    GLuint screenTexture;
    GLuint frameBuffer;
    
    std::queue<Animation*> animationQueue;
    
    FontWrapper *roboto, *robotoSmall;
    
    void createFramebuffer();
public:
    MainScene(Renderer *r, RocketteServiceImpl *service);

    void render();
    void renderFixed();
    bool update(float delta);
};

#endif /* MainScene_hpp */

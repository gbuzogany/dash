//
//  Splash.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Splash_hpp
#define Splash_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include "Definitions.h"
#include "Scene.hpp"
#include "Animation.hpp"

class Splash : Scene {
    GLuint dissolveRampTextureId;
    GLuint dissolveNoiseTextureId;
    GLuint splashLogo;
    
    float totalTime = 0;
    float dissolve = 0;

    std::queue<Animation*> animationQueue;

public:
    Splash(Renderer *r, DashServiceImpl *service);
    bool render(float delta);
    void renderFixed();
};

#endif /* Splash_hpp */
